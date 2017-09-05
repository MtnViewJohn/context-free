#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
    connect(this, SIGNAL(closeDialog()), this, SLOT(accept()));

    QSettings s("contextfreeart.org", "ContextFree");
    ui->fpsBox->setValue(s.value("output_fps", 30).toInt());
    ui->minSizeBox->setValue(s.value("output_minsize", 0.3).toDouble());
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::saveSettings() {
    QSettings s("contextfreeart.org", "ContextFree");
    s.setValue("output_fps", ui->fpsBox->value());
    s.setValue("output_minsize", ui->minSizeBox->value());
    emit closeDialog();
}
