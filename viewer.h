#ifndef VIEWER_H
#define VIEWER_H

#include "ui_SimpleView.h"
#include <QMainWindow>

#include <vtkDICOMImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <itkObjectFactory.h>
#include <vtkMarchingCubes.h>
#include <vtkImageFlip.h>
#include <vtkPolyDataMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include "itkImageToVTKImageFilter.h"
#include "itkCastImageFilter.h"

#include <CommonHeaders.h>


///// double check headers
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkAutoInit.h>
#include <vtkImageSliceMapper.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkTextMapper.h>// needed to easily convert int to std::string
#include <vtkTextProperty.h>
#include <vtkVersion.h>
#include <vtkVoxelModeller.h>
#include <vtkXMLPolyDataReader.h>
///

#include <itkBinaryThresholdImageFilter.h>
#include "itkCurvatureFlowImageFilter.h"

using BinaryThresholdFilter= itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using CurvatureFlowImageFilterType = itk::CurvatureFlowImageFilter< InputImageType, InputImageType>;
using ConnectorType = itk::ImageToVTKImageFilter<OutputImageType>;
using CastingFilterType = itk::CastImageFilter< InputImageType, OutputImageType>;

class Viewer: public QMainWindow , private Ui::SimpleView
{
    Q_OBJECT
public:
    Viewer();


    void readDicomData(std::string folder);
    void setViewer();
    void showCropTool();
    const vtkSmartPointer<vtkImageViewer2> getImageViewer() const;
    void updateCurrentSlice(int position);
    void objExporter(std::string path);
    vtkSmartPointer<vtkImageFlip> flipImage(vtkSmartPointer<vtkImageData> inputData, int flipAxis=1);

    void show3dModel(BinaryThresholdFilter::Pointer volume1,
                     BinaryThresholdFilter::Pointer volume2);
    template<typename T>
    void renderVolume(T processedImage);


private:

    template<typename T>
    vtkSmartPointer<vtkMarchingCubes> extractSurface(T inputData);
    template<typename T>
    vtkSmartPointer<vtkMarchingCubes> get3DSurface(T inputImage );
    template<typename T>
    vtkSmartPointer<vtkImageData> getVtkVolumeFromItkFilter(T inputImage);
    template<typename T>
    ConnectorType::Pointer castItkToVtk(T inputData);


    void initMapper(vtkSmartPointer<vtkPolyDataMapper> mapper, vtkSmartPointer<vtkMarchingCubes> surface);
    void initActor(vtkSmartPointer<vtkActor> actor, vtkSmartPointer<vtkPolyDataMapper> mapper);
    void initRenderer();
    void updateImageViewer(vtkSmartPointer<vtkImageFlip> flipXFilter);



    vtkSmartPointer<vtkDICOMImageReader> readervtk = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkImageViewer2> imageViewer= vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor>     renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderWindow> vtkrenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkPolyDataMapper> rightmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> rightactor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkPolyDataMapper> leftmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> leftactor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow>    renderWindowOpenGL2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
};

template<typename T>
void Viewer::renderVolume(T processedImage){

    auto volume = getVtkVolumeFromItkFilter(processedImage);
    auto flipXFilter = flipImage(volume);
    updateImageViewer(flipXFilter);
}

template<typename T>
vtkSmartPointer<vtkImageData> Viewer::getVtkVolumeFromItkFilter(T inputImage){

    auto connector = castItkToVtk(inputImage);
    auto volume = vtkSmartPointer<vtkImageData>::New();
    volume->DeepCopy(connector->GetOutput());
    return volume;
}

template<typename T>
ConnectorType::Pointer Viewer::castItkToVtk(T inputData)
{
    auto caster = CastingFilterType::New();
    auto connector = ConnectorType::New();

    caster->SetInput(inputData->GetOutput());
    connector->SetInput(caster->GetOutput());
    connector->Update();

    return connector;
}
#endif // VIEWER_H
