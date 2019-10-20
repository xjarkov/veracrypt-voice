#include <boost/process.hpp>

#include "ConfirmResetDialog.h"
#include "VoiceDialog.h"
#include "System.h"
#include "Main/GraphicUserInterface.h"


namespace VeraCrypt
{
    VoiceDialog::VoiceDialog (wxWindow *parent, boost::process::opstream &input, boost::process::ipstream &output, bool &isNormalListenerRunning, bool& isSafeListenerRunning, std::unique_ptr<boost::process::child> &listener)
        : VoiceDialogBase (parent),
        listenerInput(input),
        listenerOutput(output),
        isNormalListenerRunning(isNormalListenerRunning),
        isSafeListenerRunning(isSafeListenerRunning),
        listener(listener)
    {
        if (isNormalListenerRunning) {
            StartStopListeningButton->SetLabel(wxString::FromAscii("Stop listening"));
        } else {
            StartStopListeningButton->SetLabel(wxString::FromAscii("Start listening"));
        }
        if (isSafeListenerRunning) {
            StartSafeModeButton->SetLabel(wxString::FromAscii("Stop safe mode"));
        } else {
            StartSafeModeButton->SetLabel(wxString::FromAscii("Start safe mode"));
        }
        this->showVisual = false;
        Layout();
        Fit();
        Center();
    }

    void VoiceDialog::OnWakeRecordButtonClick(wxCommandEvent& event)
    {
        if (isRecordingNonWake) {
            return;
        }

        if (isRecordingWake) {
            isRecordingWake = false;
            WakeRecordButton->SetLabel(wxString::FromAscii("Record Wake Word"));
            recorderInput << "terminate\n";
            recorderInput.flush();
        } else {
            isRecordingWake = true;
            WakeRecordButton->SetLabel(wxString::FromAscii("Press to stop..."));
            recorderInput << "wake\n";
            recorderInput.flush();
        }
    }

    void VoiceDialog::OnNonWakeRecordButtonClick(wxCommandEvent &event)
    {
        if (isRecordingWake) {
            return;
        }

        if (isRecordingNonWake) {
            isRecordingNonWake = false;
            NonWakeRecordButton->SetLabel(wxString::FromAscii("Record Non-Wake Word"));
            recorderInput << "terminate\n";
            recorderInput.flush();
        } else {
            isRecordingNonWake = true;
            NonWakeRecordButton->SetLabel(wxString::FromAscii("Press to stop..."));
            recorderInput << "notwake\n";
            recorderInput.flush();
        }
    }

    void VoiceDialog::OnPurgeFilesButtonClick(wxCommandEvent &event)
    {
        ConfirmResetDialog dialog(this);
        dialog.ShowModal();
    }

    void VoiceDialog::OnTrainModelButtonClick(wxCommandEvent &event)
    {
        if (isNormalListenerRunning || isSafeListenerRunning) {
            return;
        }
        boost::process::child c("python3 ./Precise/train.py -e 250 model.net model/");
        c.wait();
    }

    void VoiceDialog::OnStartModelButtonClick(wxCommandEvent &event)
    {
        if (isSafeListenerRunning) {
            return;
        }
        isNormalListenerRunning = !isNormalListenerRunning;
        if (isNormalListenerRunning) {
            if (showVisual) {
                listenerInput << "start normal visual\n";
            } else {
                listenerInput << "start normal\n";
            }
            StartStopListeningButton->SetLabel(wxString::FromAscii("Stop listening"));
        } else {
            listenerInput << "stop\n";
            StartStopListeningButton->SetLabel(wxString::FromAscii("Start listening"));
        }
        listenerInput.flush();
    }

    void VoiceDialog::OnStartSafeModeButtonClick(wxCommandEvent &event)
    {
        if (isNormalListenerRunning) {
            return;
        }
        isSafeListenerRunning = !isSafeListenerRunning;
        if (isSafeListenerRunning) {
            if (showVisual) {
                listenerInput << "start safe visual\n";
            } else {
                listenerInput << "start safe\n";
            }
            StartSafeModeButton->SetLabel(wxString::FromAscii("Stop safe mode"));
        } else {
            listenerInput << "stop\n";
            StartSafeModeButton->SetLabel(wxString::FromAscii("Start safe mode"));
        }
        listenerInput.flush();
    }

    void VoiceDialog::OnShowVisualCheckBoxCheck(wxCommandEvent &event)
    {
        showVisual = event.IsChecked();
    }

    void VoiceDialog::OnConvertButtonClick(wxCommandEvent &event)
    {
        boost::process::child c("python3 ./Precise/convert.py model.net");
        c.wait();
    }
}
