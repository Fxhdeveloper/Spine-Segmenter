#include "vtkbordercallback.h"


vtkBorderCallback::vtkBorderCallback() {}

vtkBorderCallback *vtkBorderCallback::New()
{
    return new vtkBorderCallback;
}

void vtkBorderCallback::Execute(vtkObject *caller, unsigned long, void *)
{
    vtkBorderWidget* borderWidget{reinterpret_cast<vtkBorderWidget*>(caller)};

    // Get the display coordinates of the two corners of the box
    vtkCoordinate* lowerLeftCoordinate{
        static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPositionCoordinate()};
    vtkCoordinate* upperRightCoordinate{
        static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition2Coordinate()};

    lowerLeft = getComputedValue(lowerLeftCoordinate);
    upperRight =  getComputedValue(upperRightCoordinate);
    //FIXME: ITK::calculateRegionToCrop(lowerLeft, upperRight);
}

std::unique_ptr<double[]> vtkBorderCallback::getComputedValue(vtkCoordinate* inputCoordinate)
{
    std::unique_ptr<double[]> computedCoordinate{
        inputCoordinate->GetComputedValue(imageviewer->GetRenderer())};
    computedCoordinate[2] = 0;
    return computedCoordinate;
}

void vtkBorderCallback::SetRenderer(vtkSmartPointer<vtkRenderer> ren) { this->Renderer = ren; }

void vtkBorderCallback::SetImageActor(vtkSmartPointer<vtkImageActor> im) { this->ImageActor = im; }

void vtkBorderCallback::SetImageViewer(vtkSmartPointer<vtkImageViewer2> imgviewer) { this->imageviewer = imgviewer; }


