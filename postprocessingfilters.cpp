#include "postprocessingfilters.h"

PostProcessingFilters::PostProcessingFilters() {
  newRadius.Fill(5);
  newStructElement.SetRadius(newRadius);
  newStructElement.CreateStructuringElement();
  FillRadius.Fill(1);

  closingFilter->SetKernel(newStructElement);
  closingFilter->SetForegroundValue(2);
  closingFilter->SetSafeBorder(1);

  holeFilling->SetRadius(FillRadius);
  holeFilling->SetBackgroundValue(0);
  holeFilling->SetForegroundValue(2);
  holeFilling->SetMajorityThreshold(1);
  holeFilling->SetMaximumNumberOfIterations(10);

  GSHoleFilling->SetFullyConnected(1);
}

GSFillHolesFilterType::Pointer PostProcessingFilters::getPostProcessedImage(
    BinaryThresholdFilter::Pointer inputData) {
  binaryClosingFilter(inputData);
  iterativeHoleFillingFilter();
  grayscaleFillHoleFilter();
  return GSHoleFilling;
}

void PostProcessingFilters::binaryClosingFilter(
    BinaryThresholdFilter::Pointer inputData) {
  closingFilter->SetInput(inputData->GetOutput());
  closingFilter->Update();
}

void PostProcessingFilters::iterativeHoleFillingFilter() {
  holeFilling->SetInput(closingFilter->GetOutput());
  holeFilling->Update();
}

void PostProcessingFilters::grayscaleFillHoleFilter() {
  GSHoleFilling->SetInput(holeFilling->GetOutput());
  GSHoleFilling->Update();
}
