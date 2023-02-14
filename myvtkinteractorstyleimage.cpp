#include "myvtkinteractorstyleimage.h"


void myVtkInteractorStyleImage::SetImageViewer( vtkSmartPointer<vtkImageViewer2> imgViewer) {
    ImageViewer = imgViewer;
    MinSlice = ImageViewer->GetSliceMin();
    MaxSlice = ImageViewer->GetSliceMax();
    Slice = MinSlice;
}


void myVtkInteractorStyleImage::OnMouseWheelForward() {
    NextSlice();
}


void myVtkInteractorStyleImage::OnMouseWheelBackward() {
    previousSlice();
}


void myVtkInteractorStyleImage::NextSlice() {
    if (Slice < MaxSlice) {
        Slice++;
        updateViewer();
    }
}


void myVtkInteractorStyleImage::previousSlice() {
    if (Slice > MinSlice) {
        Slice--;
        updateViewer();
    }
}


void myVtkInteractorStyleImage::updateViewer()
{
    ImageViewer->SetSlice(Slice);
    ImageViewer->Render();
}
