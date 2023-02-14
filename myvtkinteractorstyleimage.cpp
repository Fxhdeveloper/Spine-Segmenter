#include "myvtkinteractorstyleimage.h"

void myVtkInteractorStyleImage::SetImageViewer(vtkImageViewer2 *imageViewer) {
    _ImageViewer = imageViewer;
    _MinSlice = imageViewer->GetSliceMin();
    _MaxSlice = imageViewer->GetSliceMax();
    _Slice = _MinSlice;
    cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice << std::endl;
}

void myVtkInteractorStyleImage::MoveSliceForward() {
    if (_Slice < _MaxSlice) {
        _Slice += 1;
        GlobalSlice = _Slice;
        _ImageViewer->SetSlice(_Slice);
        _ImageViewer->Render();
    }
}

void myVtkInteractorStyleImage::MoveSliceBackward() {
    if (_Slice > _MinSlice) {
        _Slice -= 1;
        GlobalSlice = _Slice;
        _ImageViewer->SetSlice(_Slice);
        _ImageViewer->Render();
    }
}

void myVtkInteractorStyleImage::OnMouseWheelForward() {
    //std::cout << "Scrolled mouse wheel forward." << std::endl;
    MoveSliceForward();
}

void myVtkInteractorStyleImage::OnMouseWheelBackward() {
    //std::cout << "Scrolled mouse wheel backward." << std::endl;
    if (_Slice > _MinSlice) {
        MoveSliceBackward();
    }
}
