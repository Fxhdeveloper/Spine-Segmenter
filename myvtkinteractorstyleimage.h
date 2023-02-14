#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H

#include <vtkInteractorStyleImage.h>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>

// Define own interaction style
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage)
    void SetImageViewer(vtkSmartPointer<vtkImageViewer2> imgViewer);

protected:
    void NextSlice();

    void previousSlice();

    virtual void OnMouseWheelForward();

    virtual void OnMouseWheelBackward();

    vtkSmartPointer<vtkImageViewer2> ImageViewer;
    int Slice{};
    int MinSlice{};
    int MaxSlice{};

private:
    void updateViewer();
};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
