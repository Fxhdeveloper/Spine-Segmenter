#ifndef VTKBORDERCALLBACK_H
#define VTKBORDERCALLBACK_H

#include <vtkBorderWidget.h>
#include <vtkBorderRepresentation.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>
#include <vtkCommand.h>
#include <vtkCoordinate.h>

class vtkBorderCallback : public vtkCommand
{
public:
    vtkBorderCallback();

    static vtkBorderCallback *New();
    virtual void Execute(vtkObject *caller, unsigned long, void*);

    void SetRenderer(vtkSmartPointer<vtkRenderer> ren);
    void SetImageActor(vtkSmartPointer<vtkImageActor> im);
    void SetImageViewer(vtkSmartPointer<vtkImageViewer2> imgviewer);

private:
    std::unique_ptr<double[]> getComputedValue(vtkCoordinate *inputCoordinate);

    vtkSmartPointer<vtkRenderer> Renderer;
    vtkSmartPointer<vtkImageActor> ImageActor;
    vtkSmartPointer<vtkImageViewer2> imageviewer;
    std::unique_ptr<double[]> lowerLeft;
    std::unique_ptr<double[]> upperRight;
};



#endif // VTKBORDERCALLBACK_H

