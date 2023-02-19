#include "RenderWindowUIMultipleInheritance.h"
#include "ui_SimpleView.h"
#include "vtkbordercallback.h"
#include "myvtkinteractorstyleimage.h"

vtkStandardNewMacro(myVtkInteractorStyleImage)
vtkSmartPointer<myVtkInteractorStyleImage>  myInteractorStyle =
        vtkSmartPointer<myVtkInteractorStyleImage>::New();

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

    itkObject->MinSlice = imageViewer->GetSliceMin();
    itkObject->MaxSlice = imageViewer->GetSliceMax();

    label_3->setText("Slice: Min = " + QString::number(itkObject->MinSlice) + ", Max = " + QString::number(itkObject->MaxSlice));

    ShowCropTool();
}


void RenderWindowUIMultipleInheritance::on_UpperThreshold_valueChanged(int value)
{
    label->setText("The value is " + QString::number(value));
    theUpperThreshold = value;
    updateLabel();
    callThresholdFilter();
}


void RenderWindowUIMultipleInheritance::on_LowerThreshold_valueChanged(int value)
{
    label_2->setText("The value is " + QString::number(value));
    theLowerThreshold = value;
    updateLabel();
    callThresholdFilter();
}


void RenderWindowUIMultipleInheritance::updateLabel()
{
    if (theLowerThreshold < theUpperThreshold) {
        label_3->setText(" ");
    }
    else{
        label_3->setText("The Upper Threshold value needs to be higher");
    }
}


void RenderWindowUIMultipleInheritance::callThresholdFilter()
{
    if (theLowerThreshold < theUpperThreshold) {
        Threshold();
    }
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

    vtkSmartPointer<myVtkInteractorStyleImage> interactorStyle =
            vtkSmartPointer<myVtkInteractorStyleImage>::New();

    interactorStyle->SetImageViewer(imageViewer);
    imageViewer->SetupInteractor(renderWindowInteractor);

    renderWindowInteractor->SetInteractorStyle(interactorStyle);

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    borderWidget->On();
    renderWindowInteractor->Start();
}

template<typename T>
auto RenderWindowUIMultipleInheritance::castDataItkToVtk(T inputData)
{
    CastingFilterType::Pointer caster = CastingFilterType::New();
    ConnectorType::Pointer connector = ConnectorType::New();

    caster->SetInput(inputData->GetOutput());
    connector->SetInput(caster->GetOutput());
    connector->Update();

    return connector;
}


void RenderWindowUIMultipleInheritance::on_Crop_clicked() {

    itkObject->crop();
    itkObject->smooth();

    ConnectorType::Pointer connector1 = castDataItkToVtk(itkObject->getSmoothedData());

    vtkSmartPointer<vtkImageData> volume1 = vtkSmartPointer<vtkImageData>::New();
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

    //Intervertebrae Disks
    itkObject->BinaryThreshold(thresholdFilterIntervertebrae, theLowerThreshold, theUpperThreshold);

    auto connector = castDataItkToVtk(thresholdFilterIntervertebrae);
    volumeIntervertebrae->DeepCopy(connector->GetOutput());


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
    //Intervertebrae Disks
    itkObject->BinaryThreshold(thresholdFilterCord, 230, 441);
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
    auto connector1 =castDataItkToVtk(GSHoleFilling);
    volumeIntervertebrae->DeepCopy(connector1->GetOutput());

    //Cord
    auto connector2 =castDataItkToVtk(GSHoleFilling2);
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

