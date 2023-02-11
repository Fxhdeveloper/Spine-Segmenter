#include "itk.h"
#include <itkGDCMImageIO.h>
#include "itkGDCMSeriesFileNames.h"

typedef itk::GDCMSeriesFileNames                NamesGeneratorType;
typedef itk::GDCMImageIO                        ImageIOType;

ITK::ITK()
{
    reader = itk::ImageSeriesReader< InputImageType >::New();
}

void ITK::readDicom(std::string folder)
{
    NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
    namesGenerator->SetInputDirectory(folder.c_str());
    const itk::ImageSeriesReader< InputImageType >
            ::FileNamesContainer & filenames = namesGenerator->GetInputFileNames();
    ImageIOType::Pointer gdcmIO= ImageIOType::New();
    reader->SetImageIO(gdcmIO);
    reader->SetFileNames(filenames);
    try
    {
        reader->Update();
        std::cout << "ITK reader succedded" << std::endl;
    }
    catch (itk::ExceptionObject &excp)
    {
        std::cerr << "Exception thrown while writing the image" << std::endl;
        std::cerr << excp << std::endl;
        // return EXIT_FAILURE;
    }
}

itk::ImageSeriesReader<InputImageType>::Pointer ITK::getReader()
{
    return reader;
}
