#include <boost/process.hpp>

#include "ConfirmResetDialog.h"
#include "VoiceDialog.h"
#include "System.h"
#include "Main/GraphicUserInterface.h"


namespace VeraCrypt
{
    VoiceDialog::VoiceDialog (wxWindow *parent)
        : VoiceDialogBase (parent)
    {
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
            input << "terminate\n";
            input.flush();
        } else {
            isRecordingWake = true;
            WakeRecordButton->SetLabel(wxString::FromAscii("Press to stop..."));
            input << "wake\n";
            input.flush();
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
            input << "terminate\n";
            input.flush();
        } else {
            isRecordingNonWake = true;
            NonWakeRecordButton->SetLabel(wxString::FromAscii("Press to stop..."));
            input << "notwake\n";
            input.flush();
        }
    }

    void VoiceDialog::OnPurgeFilesButtonClick(wxCommandEvent &event)
    {
        ConfirmResetDialog dialog(this);
        dialog.ShowModal();
    }

    //p
    void VoiceDialog::OnTrainModelButtonClick(wxCommandEvent &event)
    {
        boost::process::child c("python3 ./Precise/train.py -e 60 model.net recordings/");
        c.wait();
    }
}
