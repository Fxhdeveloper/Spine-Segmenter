#ifndef POSTPROCESSINGFILTERS_H
#define POSTPROCESSINGFILTERS_H

#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"
#include <itkBinaryThresholdImageFilter.h>
#include "itkGrayscaleFillholeImageFilter.h"

typedef double InputPixelType;
typedef double OutputPixelType;
const unsigned int InputDimension = 3;
using OutputImageType = itk::Image<OutputPixelType, InputDimension>;
using InputImageType = itk::Image<InputPixelType, InputDimension>;

using StructuringElementType = itk::BinaryBallStructuringElement< OutputImageType::PixelType, 3 >;
using CloseType = itk::BinaryMorphologicalClosingImageFilter < OutputImageType, OutputImageType, StructuringElementType >;
using IterativeFillHolesFilterType = itk::VotingBinaryIterativeHoleFillingImageFilter< OutputImageType >;
using BinaryThresholdFilter = itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using GSFillHolesFilterType = itk::GrayscaleFillholeImageFilter< OutputImageType, OutputImageType >;



class PostProcessingFilters
{
public:
    PostProcessingFilters();
    GSFillHolesFilterType::Pointer getPostProcessedImage(BinaryThresholdFilter::Pointer inputData);

private:
    void binaryClosingFilter(BinaryThresholdFilter::Pointer inputData);
    void iterativeHoleFillingFilter();
    void grayscaleFillHoleFilter();


    CloseType::Pointer closingFilter = CloseType::New();
    IterativeFillHolesFilterType::Pointer holeFilling = IterativeFillHolesFilterType::New();
    GSFillHolesFilterType::Pointer GSHoleFilling = GSFillHolesFilterType::New();
    StructuringElementType newStructElement;
    StructuringElementType::SizeType newRadius;
    OutputImageType::SizeType FillRadius;
};

#endif // POSTPROCESSINGFILTERS_H
