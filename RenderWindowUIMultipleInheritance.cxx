#include "RenderWindowUIMultipleInheritance.h"
#include "ui_SimpleView.h"

class vtkBorderCallback : public vtkCommand
{
public:
    vtkBorderCallback() {}


    static vtkBorderCallback *New()
    {
        return new vtkBorderCallback;
    }

    double* lowerLeft;
    double* upperRight;

    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
        vtkBorderWidget *borderWidget =
                reinterpret_cast<vtkBorderWidget*>(caller);

        // Get the display coordinates of the two corners of the box
        vtkCoordinate* lowerLeftCoordinate = static_cast<vtkBorderRepresentation*>
                (borderWidget->GetRepresentation())->GetPositionCoordinate();

        //lowerLeft = lowerLeftCoordinate->GetComputedWorldValue(this->Renderer);
        lowerLeft = lowerLeftCoordinate->GetComputedValue(imageviewer->GetRenderer());
        std::cout << "Lower left coordinate: " << lowerLeft[0] << ", " << lowerLeft[1] << std::endl;
        lowerLeft[2] = 0;

        //vtkCoordinate* upperRightCoordinate = static_cast<vtkBorderRepresentation*>
        //	(borderWidget->GetRepresentation())->GetPositionCoordinate();

        vtkCoordinate* upperRightCoordinate = static_cast<vtkBorderRepresentation*>
                (borderWidget->GetRepresentation())->GetPosition2Coordinate();

        //upperRight = upperRightCoordinate->GetComputedWorldValue(this->Renderer);
        upperRight = upperRightCoordinate->GetComputedValue(imageviewer->GetRenderer());
        std::cout << "Upper right coordinate: " << upperRight[0] << ", " << upperRight[1] << std::endl;
        upperRight[2] = 0;
        cout << endl<< endl;

        RenderWindowUIMultipleInheritance::CropVolume(lowerLeft, upperRight);

    }



    //void SetCoordinates(InputImageType::IndexType **cropStart, InputImageType::IndexType **cropEnd){
    //
    //
    //	//InputImageType::IndexType cropStart;
    //	cropStart[0] = lowerLeft[0];
    //	cropStart[1] = lowerLeft[1];
    //	cropStart[2] = lowerLeft[2];
    //	//InputImageType::IndexType cropEnd;
    //	cropEnd[0] = upperRight[0];
    //	cropEnd[1] = upperRight[1];
    //	cropEnd[2] = upperRight[2];
    //
    //		}

    void SetRenderer(vtkSmartPointer<vtkRenderer> ren) { this->Renderer = ren; }
    void SetImageActor(vtkSmartPointer<vtkImageActor> im) { this->ImageActor = im; }
    void SetImageViewer(vtkSmartPointer<vtkImageViewer2> imgviewer) { this->imageviewer = imgviewer; }

private:
    vtkSmartPointer<vtkRenderer> Renderer;
    vtkSmartPointer<vtkImageActor> ImageActor;
    vtkSmartPointer<vtkImageViewer2> imageviewer;

};




// Define own interaction style
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage)

    protected:
        vtkImageViewer2 * _ImageViewer;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;

public:
    void SetImageViewer(vtkImageViewer2* imageViewer) {
        _ImageViewer = imageViewer;
        _MinSlice = imageViewer->GetSliceMin();
        _MaxSlice = imageViewer->GetSliceMax();
        _Slice = _MinSlice;
        cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice << std::endl;
    }
    int GlobalSlice = 0;

protected:
    void MoveSliceForward() {
        if (_Slice < _MaxSlice) {
            _Slice += 1;
            GlobalSlice = _Slice;
            _ImageViewer->SetSlice(_Slice);
            _ImageViewer->Render();
        }
    }

    void MoveSliceBackward() {
        if (_Slice > _MinSlice) {
            _Slice -= 1;
            GlobalSlice = _Slice;
            _ImageViewer->SetSlice(_Slice);
            _ImageViewer->Render();
        }
    }

    /*
    virtual void OnKeyDown() {
    std::string key = this->(ui->qvtkwidget_2->GetInteractor()->GetKeySym();
    if (key.compare("Up") == 0) {
    //cout << "Up arrow key was pressed." << endl;
    MoveSliceForward();
    }
    else if (key.compare("Down") == 0) {
    //cout << "Down arrow key was pressed." << endl;
    MoveSliceBackward();
    }
    // forward event
    vtkInteractorStyleImage::OnKeyDown();
    }
    */

    virtual void OnMouseWheelForward() {
        //std::cout << "Scrolled mouse wheel forward." << std::endl;
        MoveSliceForward();
    }

    virtual void OnMouseWheelBackward() {
        //std::cout << "Scrolled mouse wheel backward." << std::endl;
        if (_Slice > _MinSlice) {
            MoveSliceBackward();
        }
    }
};

vtkStandardNewMacro(myVtkInteractorStyleImage)



vtkSmartPointer<myVtkInteractorStyleImage>  myInteractorStyle =
        vtkSmartPointer<myVtkInteractorStyleImage>::New();



// Constructor
RenderWindowUIMultipleInheritance::RenderWindowUIMultipleInheritance()
{

    this->setupUi(this);

    // Set up action signals and slots
    connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    QObject::connect(this->UpperThreshold, SIGNAL(valueChanged), this, SLOT(on_UpperThreshold_valueChanged(int)));

    renderer->SetBackground(.1, .2, .3);
    actor->SetMapper(mapper);
    renderer->AddActor(actor);

    Up_Threshold->setText("Set Upper Threshold");
    Low_Threshold->setText("Set Lower Threshold");
    label_2->setText("the value is 0");
    label->setText("the value is 0");

};

std::string RenderWindowUIMultipleInheritance::getDicomImagesFolder()
{
    QString nameoffile = QFileDialog::getExistingDirectory(this, "Open Dicom Folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
    std::string folder = nameoffile.toUtf8().constData();

    return folder;
}


void RenderWindowUIMultipleInheritance::on_ReadData_clicked() {

    std::string folder = getDicomImagesFolder();
    itkObject->readDicom(folder);





    readervtk->SetDirectoryName(folder.c_str());
    readervtk->Update();
    imageViewer->SetInputConnection(readervtk->GetOutputPort());



    qvtkWidget->SetRenderWindow(renderWindow);
    renderWindowInteractor = qvtkWidget->GetInteractor();

    imageViewer->SetRenderWindow(qvtkWidget->GetRenderWindow());
    myInteractorStyle->SetImageViewer(imageViewer);

    imageViewer->SetupInteractor(renderWindowInteractor);
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    MinSlice = imageViewer->GetSliceMin();
    MaxSlice = imageViewer->GetSliceMax();



    label_3->setText("Slice: Min = " + QString::number(MinSlice) + ", Max = " + QString::number(MaxSlice));

    ShowCropTool();
}

void RenderWindowUIMultipleInheritance::on_UpperThreshold_valueChanged(int value)
{
    label->setText("the value is " + QString::number(value));
    theUpperThreshold = value;
    label_3->setText(" ");
    if (theLowerThreshold < theUpperThreshold) {
        Threshold();
        label_3->setText(" ");
    }
    else
        label_3->setText("The Upper Threshold value needs to be higher");
}

void RenderWindowUIMultipleInheritance::on_LowerThreshold_valueChanged(int value)
{

    label_2->setText("the value is " + QString::number(value));
    theLowerThreshold = value;
    if (theLowerThreshold < theUpperThreshold) {
        Threshold();
        label_3->setText(" ");
    }
    else
        label_3->setText("The Upper Threshold value needs to be higher");
}

void RenderWindowUIMultipleInheritance::on_DCM_Slice_change_sliderMoved(int position)
{
    imageViewer->SetSlice(position);
    imageViewer->Render();
}

void RenderWindowUIMultipleInheritance::ShowCropTool() {

    // create an interactor with our own style (inherit from vtkInteractorStyleImage)
    // in order to catch mousewheel and key events
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkBorderWidget> borderWidget =
            vtkSmartPointer<vtkBorderWidget>::New();
    borderWidget->SetInteractor(renderWindowInteractor);
    static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->
            GetBorderProperty()->SetColor(1, 0, 0);
    borderWidget->SelectableOff();


    vtkSmartPointer<vtkBorderCallback> borderCallback =
            vtkSmartPointer<vtkBorderCallback>::New();

    borderCallback->SetImageViewer(imageViewer);
    borderWidget->AddObserver(vtkCommand::InteractionEvent, borderCallback);


    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
            vtkSmartPointer<myVtkInteractorStyleImage>::New();

    myInteractorStyle->SetImageViewer(imageViewer);
    imageViewer->SetupInteractor(renderWindowInteractor);

    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    borderWidget->On();
    renderWindowInteractor->Start();
}

void RenderWindowUIMultipleInheritance::CropVolume(double *x, double *y) {

    InputImageType::IndexType cropStart;
    cropStart[0] = x[0]-120;
    cropStart[1] = 590 - y[1]- 35;//-88
    cropStart[2] = MinSlice; //x[2];

    InputImageType::IndexType cropEnd;
    cropEnd[0] = y[0]-88;//
    cropEnd[1] = 590 - x[1]-15 ;//-44
    cropEnd[2] = MaxSlice;  // x[2];

    cout << "the cropping parameters seem to be lowerLeft= " << cropStart[0] << "," << cropStart[1] << "," << cropStart[2] << endl;
    cout << "the cropping parameters seem to be uoperRight= " << cropEnd[0] << "," << cropEnd[1] << "," << cropEnd[2] << endl;


    InputImageType::RegionType DesiredRegion;
    InputImageType::SizeType cropSize;
    cropSize[0] = cropEnd[0] - cropStart[0] ;
    cropSize[1] = cropEnd[1] - cropStart[1] ;
    cropSize[2] = cropEnd[2] - cropStart[2];

    DesiredRegion.SetSize(cropSize);
    DesiredRegion.SetIndex(cropStart);

    //DesiredRegion.SetUpperIndex(cropEnd);

    ROIFilter->SetRegionOfInterest(DesiredRegion);


}

void RenderWindowUIMultipleInheritance::on_Crop_clicked() {


    ROIFilter->SetInput(itkObject->getReader()->GetOutput());
    ROIFilter->Update();

    //************ Smoothing Filter ********************************

    smoothing->SetInput(ROIFilter->GetOutput());
    smoothing->SetNumberOfIterations(10);
    smoothing->SetTimeStep(0.05);
    smoothing->Update();
    //************ Smoothing Filter finished ********************************//

    typedef itk::CastImageFilter< InputImageType, OutputImageType >  CastingFilterType;
    CastingFilterType::Pointer caster1 = CastingFilterType::New();

    typedef itk::ImageToVTKImageFilter<OutputImageType>       ConnectorType;
    ConnectorType::Pointer connector1 = ConnectorType::New();

    vtkSmartPointer<vtkImageData> volume1 = vtkSmartPointer<vtkImageData>::New();

    caster1->SetInput(smoothing->GetOutput());
    connector1->SetInput(caster1->GetOutput());
    connector1->Update();
    volume1->DeepCopy(connector1->GetOutput());


    vtkSmartPointer<vtkImageFlip> flipXFilter =
            vtkSmartPointer<vtkImageFlip>::New();
    flipXFilter->SetFilteredAxis(1); // flip x axis
    flipXFilter->SetInputData(volume1);
    flipXFilter->Update();



    imageViewer->SetInputConnection(flipXFilter->GetOutputPort());
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();




}

void RenderWindowUIMultipleInheritance::Threshold(void) {

    //Filtering



    //Intervertebrae Disks
    thresholdFilterIntervertebrae->SetInput(smoothing->GetOutput());
    thresholdFilterIntervertebrae->SetLowerThreshold(theLowerThreshold);
    thresholdFilterIntervertebrae->SetUpperThreshold(theUpperThreshold);
    thresholdFilterIntervertebrae->Update();


    typedef itk::CastImageFilter< InputImageType, OutputImageType >  CastingFilterType;
    CastingFilterType::Pointer caster1 = CastingFilterType::New();

    typedef itk::ImageToVTKImageFilter<OutputImageType>       ConnectorType;
    ConnectorType::Pointer connector1 = ConnectorType::New();


    caster1->SetInput(thresholdFilterIntervertebrae->GetOutput());
    connector1->SetInput(caster1->GetOutput());
    connector1->Update();
    volumeIntervertebrae->DeepCopy(connector1->GetOutput());


    vtkSmartPointer<vtkImageFlip> flipXFilter =
            vtkSmartPointer<vtkImageFlip>::New();
    flipXFilter->SetFilteredAxis(1); // flip x axis
    flipXFilter->SetInputData(volumeIntervertebrae);
    flipXFilter->Update();



    imageViewer->SetInputConnection(flipXFilter->GetOutputPort());
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();


}

void RenderWindowUIMultipleInheritance::ThresholdCord(void) {

    //Filtering
    //Intervertebrae Disks
    thresholdFilterCord->SetInput(smoothing->GetOutput());
    thresholdFilterCord->SetLowerThreshold(230);
    thresholdFilterCord->SetUpperThreshold(441);
    thresholdFilterCord->Update();


    //typedef itk::CastImageFilter< InputImageType, OutputImageType >  CastingFilterType;
    //CastingFilterType::Pointer caster1 = CastingFilterType::New();

    //typedef itk::ImageToVTKImageFilter<OutputImageType>       ConnectorType;
    //ConnectorType::Pointer connector1 = ConnectorType::New();

    //

    //caster1->SetInput(thresholdFilterCord->GetOutput());
    //connector1->SetInput(caster1->GetOutput());
    //connector1->Update();
    //volumeCord->DeepCopy(connector1->GetOutput());



}

void RenderWindowUIMultipleInheritance::Print(void) {
    QFont fontBold("Arial", 12, QFont::Bold);
    QFont font("Arial", 12);
    //	label_3->setText("3D Model loading");
    label_3->setFont(font);
    label_3->setText("Please wait! The 3D Model is loading...");
}

void RenderWindowUIMultipleInheritance::on_ShowModel_clicked() {


    Print();
    ThresholdCord();

    /****** CLOSING AND HOLE FILLING TO IMPROVE THE SEGMENTATION RESULT ********/

    StructuringElementType newStructElement;
    StructuringElementType::SizeType newRadius;
    newRadius.Fill(5);
    newStructElement.SetRadius(newRadius);
    newStructElement.CreateStructuringElement();
    OutputImageType::SizeType FillRadius;
    FillRadius.Fill(1);
    //1
    newClosing->SetInput(thresholdFilterIntervertebrae->GetOutput());
    newClosing->SetKernel(newStructElement);
    newClosing->SetForegroundValue(2);
    newClosing->SetSafeBorder(1);
    newClosing->Update();

    HoleFilling->SetInput(newClosing->GetOutput());
    HoleFilling->SetRadius(FillRadius);
    HoleFilling->SetBackgroundValue(0);
    HoleFilling->SetForegroundValue(2);
    HoleFilling->SetMajorityThreshold(1);
    HoleFilling->SetMaximumNumberOfIterations(10);
    HoleFilling->Update();

    GSHoleFilling->SetInput(HoleFilling->GetOutput());
    GSHoleFilling->SetFullyConnected(1);
    GSHoleFilling->Update();

    //2///////////////////////////////////
    newClosing2->SetInput(thresholdFilterCord->GetOutput());
    newClosing2->SetKernel(newStructElement);
    newClosing2->SetForegroundValue(2);
    newClosing2->SetSafeBorder(1);
    newClosing2->Update();

    HoleFilling2->SetInput(newClosing2->GetOutput());
    HoleFilling2->SetRadius(FillRadius);
    HoleFilling2->SetBackgroundValue(0);
    HoleFilling2->SetForegroundValue(2);
    HoleFilling2->SetMajorityThreshold(1);
    HoleFilling2->SetMaximumNumberOfIterations(10);
    HoleFilling2->Update();

    GSHoleFilling2->SetInput(HoleFilling2->GetOutput());
    GSHoleFilling2->SetFullyConnected(1);
    GSHoleFilling2->Update();
    //*************** Closing and Hole Filling Finished ***********//

    //Intervertebrae Disks
    caster1->SetInput(GSHoleFilling->GetOutput());
    connector1->SetInput(caster1->GetOutput());
    connector1->Update();
    volumeIntervertebrae->DeepCopy(connector1->GetOutput());

    //Cord
    caster2->SetInput(GSHoleFilling2->GetOutput());
    connector2->SetInput(caster2->GetOutput());
    connector2->Update();
    volumeCord->DeepCopy(connector2->GetOutput());



    //showing the 3d model

    double Value = 1.3;

    surface->SetInputData(volumeIntervertebrae);
    surface->ComputeNormalsOn();
    surface->SetValue(0, Value);

    surface2->SetInputData(volumeCord);
    surface2->ComputeNormalsOn();
    surface2->SetValue(0, Value);

    leftmapper->SetInputConnection(surface->GetOutputPort());
    leftmapper->ScalarVisibilityOff();
    leftactor->SetMapper(leftmapper);
    leftactor->GetProperty()->SetColor(1, 0.547237, 0.319073);
    leftactor->GetProperty()->SetEdgeVisibility(.9);
    leftactor->GetProperty()->SetEdgeColor(1, 0, 0);
    leftactor->GetProperty()->SetShading(.1);
    leftactor->GetProperty()->SetOpacity(1.0);

    rightmapper->SetInputConnection(surface2->GetOutputPort());
    rightmapper->ScalarVisibilityOff();
    rightactor->SetMapper(rightmapper);
    //rightactor->GetProperty()->SetDiffuseColor(.1, .1, .1);

    vtkrenderWindow->SetSize(900, 900);

    // And one interactor
    interactor->SetRenderWindow(vtkrenderWindow);
    interactor->SetInteractorStyle(style);

    // Setup both renderers
    vtkrenderWindow->AddRenderer(leftRenderer);
    leftRenderer->SetBackground(0.329412, 0.34902, 0.427451);
    //leftRenderer->SetBackground(1, 0, 1);

    leftRenderer->AddActor(leftactor);
    leftRenderer->AddActor(rightactor);
    leftRenderer->ResetCamera();

    /*vtkrenderWindow->Render();
    interactor->Start();*/



    qvtkWidget_2->SetRenderWindow(renderWindowOpenGL2);
    qvtkWidget_2->GetRenderWindow()->AddRenderer(leftRenderer);
    qvtkWidget_2->update();

    QFont font("Arial", 12);
    label_3->setFont(font);
    label_3->setText("3D Model loaded");



}

//void RenderWindowUIMultipleInheritance::on_ShowExternal_clicked()
//{
//	vtkrenderWindow->Render();
//	interactor->Start();
//	
//}

void RenderWindowUIMultipleInheritance::on_Show_in_VR_clicked() {

    QString current_path = QDir::currentPath();
    current_path += "/myobjfile1";
    string new_path = current_path.toUtf8().constData();

    myobjexporter->SetRenderWindow(renderWindowOpenGL2);
    myobjexporter->SetFilePrefix(new_path.c_str());
    myobjexporter->Write();

    QString path = QDir::currentPath();
    path += "/Segmenter.exe";
    //label_3->setText(path);
    QDesktopServices::openUrl(QUrl("file:///" + path, QUrl::TolerantMode));//(QDir::toNativeSeparators(filename)


}

void RenderWindowUIMultipleInheritance::slotExit()
{
    qApp->exit();
}

