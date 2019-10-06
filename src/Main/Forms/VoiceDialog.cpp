#include <boost/process.hpp>

#include "ConfirmResetDialog.h"
#include "VoiceDialog.h"
#include "System.h"
#include "Main/GraphicUserInterface.h"


namespace VeraCrypt
{
    VoiceDialog::VoiceDialog (wxWindow *parent, boost::process::opstream &input, boost::process::ipstream &output, bool &isNormalListenerRunning, bool& isSafeListenerRunning)
        : VoiceDialogBase (parent),
        listenerInput(input),
        listenerOutput(output),
        isNormalListenerRunning(isNormalListenerRunning),
        isSafeListenerRunning(isSafeListenerRunning)
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
        boost::process::child c("python3 ./Precise/train.py -e 60 model.net model/");
        c.wait();
    }

    void VoiceDialog::OnStartModelButtonClick(wxCommandEvent &event)
    {
        if (isSafeListenerRunning) {
            return;
        }
        isNormalListenerRunning = !isNormalListenerRunning;
        if (isNormalListenerRunning) {
            StartStopListeningButton->SetLabel(wxString::FromAscii("Stop listening"));
            listenerInput << "start\n";
        } else {
            StartStopListeningButton->SetLabel(wxString::FromAscii("Start listening"));
            listenerInput << "stop\n";
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
            StartSafeModeButton->SetLabel(wxString::FromAscii("Stop safe mode"));
        } else {
            StartSafeModeButton->SetLabel(wxString::FromAscii("Start safe mode"));
        }
    }
}
