#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H

#include <vtkInteractorStyleImage.h>
#include <vtkImageViewer2.h>


// Define own interaction style
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage)
    void SetImageViewer(vtkImageViewer2* imageViewer);
    int GlobalSlice = 0;

protected:
    void MoveSliceForward();

    void MoveSliceBackward();

    virtual void OnMouseWheelForward();

    virtual void OnMouseWheelBackward();

    vtkImageViewer2 * _ImageViewer;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;

};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
