#include "RenderWindowUIMultipleInheritance.h"
#include "ui_SimpleView.h"

void RenderWindowUIMultipleInheritance::setLabels()
{
    Up_Threshold->setText("Set Upper Threshold");
    Low_Threshold->setText("Set Lower Threshold");
    label_2->setText("the value is 0");
    label->setText("the value is 0");
}

RenderWindowUIMultipleInheritance::RenderWindowUIMultipleInheritance()
{
    this->setupUi(this);
    QObject::connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    QObject::connect(this->UpperThreshold, SIGNAL(valueChanged), this, SLOT(on_UpperThreshold_valueChanged(int)));
    setLabels();
};

std::string RenderWindowUIMultipleInheritance::getDicomImagesFolder(){

    QString nameoffile = QFileDialog::getExistingDirectory(this, "Open Dicom Folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
    std::string folder = nameoffile.toUtf8().constData();
    return folder;
}


void RenderWindowUIMultipleInheritance::readDicom()
{
    std::string folder = getDicomImagesFolder();
    itkObject->readDicomData(folder);
    viewer->readDicomData(folder);
    viewer->setViewer();
}

void RenderWindowUIMultipleInheritance::on_ReadData_clicked() {

    readDicom();
    itkObject->MinSlice = viewer->getImageViewer()->GetSliceMin();
    itkObject->MaxSlice = viewer->getImageViewer()->GetSliceMax();
    label_3->setText("Slice: Min = " + QString::number(itkObject->MinSlice) + ", Max = " + QString::number(itkObject->MaxSlice));
    ShowCropTool();
}


void RenderWindowUIMultipleInheritance::on_UpperThreshold_valueChanged(int value){

    label->setText("The value is " + QString::number(value));
    theUpperThreshold = value;
    updateLabel();
    callThresholdFilter();
}


void RenderWindowUIMultipleInheritance::on_LowerThreshold_valueChanged(int value){

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
    viewer->updateCurrentSlice(position);
}


void RenderWindowUIMultipleInheritance::ShowCropTool() {
    viewer->showCropTool();
}


void RenderWindowUIMultipleInheritance::on_Crop_clicked() {

    itkObject->crop();
    itkObject->smooth();
    viewer->renderVolume(itkObject->getSmoothedData());
}


void RenderWindowUIMultipleInheritance::Threshold(void) {

    itkObject->BinaryThreshold(intervertebrae, theLowerThreshold, theUpperThreshold);
    viewer->renderVolume(intervertebrae);
}


void RenderWindowUIMultipleInheritance::on_ShowModel_clicked() {

    Print();
    ThresholdCord();
    //make the following function a template that can
    // take as many volumes we give, and visualize them
    viewer->show3dModel(intervertebrae, spinalCord);

    QFont font("Arial", 12);
    label_3->setFont(font);
    label_3->setText("3D Model loaded");
}
void RenderWindowUIMultipleInheritance::Print(void) {
    QFont fontBold("Arial", 12, QFont::Bold);
    QFont font("Arial", 12);
    //	label_3->setText("3D Model loading");
    label_3->setFont(font);
    label_3->setText("Please wait! The 3D Model is loading...");
}
void RenderWindowUIMultipleInheritance::ThresholdCord(void) {
    itkObject->BinaryThreshold(spinalCord, 230, 441);
}

void RenderWindowUIMultipleInheritance::on_Show_in_VR_clicked() {
    exportModel();
    openVRviewer();
}
void RenderWindowUIMultipleInheritance::exportModel(){

    QString current_path = QDir::currentPath() + "/myobjfile1";
    std::string path = current_path.toUtf8().constData();
    viewer->objExporter(path);
}
void RenderWindowUIMultipleInheritance::openVRviewer(){

    QString path = QDir::currentPath() + "/Segmenter.exe";
    QDesktopServices::openUrl(QUrl("file:///" + path, QUrl::TolerantMode));
}

void RenderWindowUIMultipleInheritance::slotExit()
{
    qApp->exit();
}

