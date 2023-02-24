#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H

#include "ui_SimpleView.h"
#include <QMainWindow>

#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkFlipImageFilter.h"
#include "itkImage.h"
#include "itkImageDuplicator.h"

#include "itkImageFileWriter.h"
#include "itkImageSeriesWriter.h"
#include "itkImageSliceIteratorWithIndex.h"

#include "itkLabelMapToBinaryImageFilter.h"
#include "itkLabelToRGBImageFilter.h"
#include "itkMaskImageFilter.h"
#include "itkMaskNegatedImageFilter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkMetaDataObject.h"
#include "itkNumericSeriesFileNames.h"
#include "itkNumericTraits.h"
#include "itkPasteImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itksys/SystemTools.hxx"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <itkAddImageFilter.h>


#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkJPEGImageIO.h>
#include <itkMaskNegatedImageFilter.h>
#include <itkNrrdImageIO.h>
#include <itkOtsuMultipleThresholdsImageFilter.h>

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
#include <vtkCamera.h>
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
#include <vtksphereSource.h>
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

using ConnectorType = itk::ImageToVTKImageFilter<OutputImageType>;
using CastingFilterType = itk::CastImageFilter< InputImageType, OutputImageType>;

using namespace std;

class RenderWindowUIMultipleInheritance : public QMainWindow , private Ui::SimpleView
{
    Q_OBJECT
public:

    RenderWindowUIMultipleInheritance();

private:
    std::unique_ptr<ITK> itkObject = std::make_unique<ITK>();
    vtkSmartPointer<vtkImageViewer2> imageViewer= vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkImageViewer2> imageViewer2= vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkImageViewer2> imageViewer3= vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkDICOMImageReader> readervtk = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    vtkSmartPointer<vtkImageSliceMapper>mapper = vtkSmartPointer<vtkImageSliceMapper>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow>    renderWindowOpenGL2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor>     renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor>     renderWindowInteractor2 = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkImageData> volumeCord=vtkSmartPointer<vtkImageData>::New();
    vtkSmartPointer<vtkImageData> volumeIntervertebrae=vtkSmartPointer<vtkImageData>::New();

    vtkSmartPointer<vtkRenderWindow> vtkrenderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkPolyDataMapper> rightmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> rightactor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
            vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkPolyDataMapper> leftmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> leftactor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkOBJExporter> myobjexporter = vtkSmartPointer<vtkOBJExporter>::New();


    BinaryThresholdFilter::Pointer intervertebrae= BinaryThresholdFilter::New();
    BinaryThresholdFilter::Pointer spinalCord= BinaryThresholdFilter::New();

    int theLowerThreshold{};
    int theUpperThreshold{};
    int GlobalActualSlice{};

    void Threshold(void);
    void ThresholdCord(void);
    void ShowCropTool();
    void Print(void);

    std::string getDicomImagesFolder();

    void updateLabel();

    void callThresholdFilter();
    template<typename T>
    ConnectorType::Pointer castItkToVtk(T inputData);

    vtkSmartPointer<vtkImageFlip> flipImage(vtkSmartPointer<vtkImageData> inputData, int flipAxis=1);
    vtkSmartPointer<vtkMarchingCubes> extractSurface(vtkSmartPointer<vtkImageData> inputData);

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
