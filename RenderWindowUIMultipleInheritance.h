#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H

#include "ui_SimpleView.h"
#include <QMainWindow>
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkFlipImageFilter.h"
#include "itkGrayscaleFillholeImageFilter.h"
#include "itkImage.h"
#include "itkImageDuplicator.h"

#include "itkImageFileWriter.h"
#include "itkImageSeriesWriter.h"
#include "itkImageSliceIteratorWithIndex.h"
#include "itkImageToVTKImageFilter.h"
#include "itkLabelMapToBinaryImageFilter.h"
#include "itkLabelToRGBImageFilter.h"
#include "itkMaskImageFilter.h"
#include "itkMaskNegatedImageFilter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkMetaDataObject.h"
#include "itkNumericSeriesFileNames.h"
#include "itkNumericTraits.h"
#include "itkPasteImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itksys/SystemTools.hxx"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <itkAddImageFilter.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkCurvatureFlowImageFilter.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkJPEGImageIO.h>
#include <itkMaskNegatedImageFilter.h>
#include <itkNrrdImageIO.h>
#include <itkOtsuMultipleThresholdsImageFilter.h>
#include <itkRegionOfInterestImageFilter.h>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <qfont.h>
#include <QMessageBox>
#include <QTemporaryDir>
#include <QuickView.h>
#include <QUrl>
#include <sstream>
#include <string>
#include <vector>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkAssemblyNode.h>
#include <vtkAssemblyPath.h>
#include <vtkAutoInit.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkCoordinate.h>
#include <vtkCubeSource.h>
#include <vtkDICOMImageReader.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageViewer.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkMarchingCubes.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkOBJExporter.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkProperty2D.h> // For setting the color in the handles
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSeedRepresentation.h>
#include <vtkSeedWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkTextMapper.h>
#include <vtkTextMapper.h>// needed to easily convert int to std::string
#include <vtkTextProperty.h>
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkVoxelModeller.h>
#include <vtkXMLPolyDataReader.h>

#include <itk.h>
// headers needed for this example
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

using namespace std;

typedef double InputPixelType;
typedef double OutputPixelType;
const unsigned int InputDimension = 3;
typedef itk::Image<OutputPixelType, InputDimension> OutputImageType;
typedef itk::Image<InputPixelType, InputDimension> InputImageType;



//typedef static itk::RegionOfInterestImageFilter <InputImageType, InputImageType> inputROIFilterType;
static itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::Pointer ROIFilter;

static int MinSlice;
static int MaxSlice;

typedef itk::CastImageFilter< InputImageType, OutputImageType >  CastingFilterType;
typedef itk::ImageToVTKImageFilter<OutputImageType>       ConnectorType;


typedef itk::BinaryThresholdImageFilter<InputImageType, InputImageType> BinarythresholdFilter;
typedef itk::BinaryBallStructuringElement< OutputImageType::PixelType, 3 > StructuringElementType;
typedef itk::BinaryMorphologicalClosingImageFilter < OutputImageType, OutputImageType, StructuringElementType > CloseType;
typedef itk::VotingBinaryIterativeHoleFillingImageFilter< OutputImageType > IterativeFillHolesFilterType;
typedef itk::GrayscaleFillholeImageFilter< OutputImageType, OutputImageType > GSFillHolesFilterType;


class RenderWindowUIMultipleInheritance : public QMainWindow , private Ui::SimpleView
{
    Q_OBJECT
public:

    RenderWindowUIMultipleInheritance();
    static void CropVolume(double *x, double *y);

    InputImageType::SizeType cropSize;




private:
    std::unique_ptr<ITK> itkObject = std::make_unique<ITK>();
    vtkSmartPointer<vtkImageViewer2> imageViewer;
    vtkSmartPointer<vtkImageViewer2> imageViewer2;
    vtkSmartPointer<vtkImageViewer2> imageViewer3;



    vtkSmartPointer<vtkDICOMImageReader> readervtk;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkImageActor> actor;
    vtkSmartPointer<vtkImageSliceMapper> mapper;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindowOpenGL2;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2;





    BinarythresholdFilter::Pointer thresholdFilterIntervertebrae;
    BinarythresholdFilter::Pointer thresholdFilterCord;
    vtkSmartPointer<vtkImageData> volumeCord;
    vtkSmartPointer<vtkImageData> volumeIntervertebrae;

    ConnectorType::Pointer connector1;
    CastingFilterType::Pointer caster1;
    ConnectorType::Pointer connector2;
    CastingFilterType::Pointer caster2;




    CloseType::Pointer newClosing ;
    CloseType::Pointer newClosing2;
    IterativeFillHolesFilterType::Pointer HoleFilling;
    GSFillHolesFilterType::Pointer GSHoleFilling ;
    IterativeFillHolesFilterType::Pointer HoleFilling2;
    GSFillHolesFilterType::Pointer GSHoleFilling2 ;


    vtkSmartPointer<vtkRenderWindow> vtkrenderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkRenderer> leftRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkPolyDataMapper> rightmapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> rightactor =
            vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
            vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkPolyDataMapper> leftmapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> leftactor =
            vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkMarchingCubes> surface =
            vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkMarchingCubes> surface2 =
            vtkSmartPointer<vtkMarchingCubes>::New();
    typedef itk::CurvatureFlowImageFilter< InputImageType, InputImageType >
    CurvatureFlowImageFilterType;
    CurvatureFlowImageFilterType::Pointer smoothing;

    vtkSmartPointer<vtkOBJExporter> myobjexporter;

    int theLowerThreshold = 0;
    int theUpperThreshold = 0;
    int GlobalActualSlice = 0;

    void Threshold(void);
    void ThresholdCord(void);
    void ShowCropTool();
    void Print(void);

    std::string getDicomImagesFolder();

private slots:
    void on_UpperThreshold_valueChanged(int value);
    void on_LowerThreshold_valueChanged(int value);
    void on_DCM_Slice_change_sliderMoved(int position);
    void on_ReadData_clicked();
    //void on_ShowExternal_clicked();
    void on_Crop_clicked();
    void on_ShowModel_clicked();
    void on_Show_in_VR_clicked();

public slots:

    virtual void slotExit();

};





#endif RenderWindowUIMultipleInheritance_H
