#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H
 
#include "ui_SimpleView.h"
#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkImageActor.h>
#include <vtkImageSliceMapper.h>
#include <vector>
#include <string>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkSTLWriter.h>
#include <vtkImageViewer.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkJPEGReader.h>
#include <vtkSTLWriter.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTemporaryDir>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkJPEGReader.h>
#include <vtkSTLWriter.h>
#include <vtkImageFlip.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <QDesktopServices>
#include <QUrl>
#include <string>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <QuickView.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkAddImageFilter.h>
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMSeriesFileNames.h"
#include <itkRegionOfInterestImageFilter.h>
#include <itkCurvatureFlowImageFilter.h>
#include <iostream>
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"
#include "itkGrayscaleFillholeImageFilter.h"
#include <itkMaskNegatedImageFilter.h>
#include "itkImageToVTKImageFilter.h"
#include "itkCastImageFilter.h"  
#include "itkRescaleIntensityImageFilter.h" 
#include "itkMaskImageFilter.h" 
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkJPEGReader.h>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>
#include <vtkImageFlip.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkAutoInit.h> 
#include <vtkRenderWindowInteractor.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h> // For setting the color in the handles
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>// needed to easily convert int to std::string
#include <sstream>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <sstream>

#include "itkMaskNegatedImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkPasteImageFilter.h"
#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkLabelMapToBinaryImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"
#include "itkFlipImageFilter.h"
#include "itkImageSliceIteratorWithIndex.h"
#include "itkImageDuplicator.h"
#include "itkGrayscaleFillholeImageFilter.h"

#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include <itkNrrdImageIO.h>
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"

#include "itkGDCMImageIO.h"

#include "itkNumericSeriesFileNames.h"
#include "itkImageFileReader.h"
#include "itkImageSeriesWriter.h"
#include "itkMetaDataObject.h"
#include "itksys/SystemTools.hxx"
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <QuickView.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkAddImageFilter.h>
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMSeriesFileNames.h"
#include <itkOtsuMultipleThresholdsImageFilter.h>
#include "itkLabelToRGBImageFilter.h"
#include "itkNumericTraits.h"
#include "itksys/SystemTools.hxx"
#include <sstream>
#include <itkJPEGImageIO.h>



#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <QuickView.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkAddImageFilter.h>
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMSeriesFileNames.h"
#include <itkOtsuMultipleThresholdsImageFilter.h>
#include "itkLabelToRGBImageFilter.h"
#include "itkNumericTraits.h"
#include "itksys/SystemTools.hxx"
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <itkImageFileWriter.h>
#include <itkJPEGImageIO.h>

#include <itkCurvatureFlowImageFilter.h>
#include <itkRegionOfInterestImageFilter.h>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkAssemblyNode.h>
#include <vtkAssemblyPath.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkCoordinate.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkPolyData.h>
#include <vtkPropPicker.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <qfont.h>
#include <itkRegionOfInterestImageFilter.h>
#include <vtkOBJExporter.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

using namespace std;

typedef double InputPixelType;
typedef double OutputPixelType;
const unsigned int InputDimension = 3;
typedef itk::Image<OutputPixelType, InputDimension> OutputImageType;
typedef itk::Image<InputPixelType, InputDimension> InputImageType;

//typedef static itk::ImageSeriesReader< InputImageType >     ReaderType;
typedef itk::GDCMImageIO                        ImageIOType;
typedef itk::GDCMSeriesFileNames                NamesGeneratorType;

//typedef static itk::RegionOfInterestImageFilter <InputImageType, InputImageType> inputROIFilterType;
static itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::Pointer ROIFilter;
static itk::ImageSeriesReader< InputImageType >::Pointer readeritk;
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
	
	vtkSmartPointer<vtkImageViewer2> imageViewer;
	vtkSmartPointer<vtkImageViewer2> imageViewer2;
	vtkSmartPointer<vtkImageViewer2> imageViewer3;



	vtkSmartPointer<vtkDICOMImageReader> reader;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkImageActor> actor;
	vtkSmartPointer<vtkImageSliceMapper> mapper;

	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindowOpenGL2;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2;
	
	ImageIOType::Pointer gdcmIO;
	NamesGeneratorType::Pointer namesGenerator; 
	
	
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