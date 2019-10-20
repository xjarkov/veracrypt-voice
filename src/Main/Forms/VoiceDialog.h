#ifndef __VoiceDialog__
#define __VoiceDialog__

#include <memory>

#include "Forms.h"
#include "Main/Main.h"
#include "Main/SystemPrecompiled.h"

/** Implementing VoiceDialogBase */
namespace VeraCrypt
{
	class VoiceDialog : public VoiceDialogBase
	{
	public:
        VoiceDialog(wxWindow *parent, boost::process::opstream &input, boost::process::ipstream &output, bool &isNormalListenerRunning, bool &isSafeListenerRunning, std::unique_ptr<boost::process::child> &listener);

    protected:
        void OnWakeRecordButtonClick(wxCommandEvent &event);
        void OnNonWakeRecordButtonClick(wxCommandEvent &event);
        void OnPurgeFilesButtonClick(wxCommandEvent &event);
        void OnTrainModelButtonClick(wxCommandEvent &event);
        void OnStartModelButtonClick(wxCommandEvent &event);
        void OnStartSafeModeButtonClick(wxCommandEvent &event);
        void OnShowVisualCheckBoxCheck(wxCommandEvent &event);
        void OnConvertButtonClick(wxCommandEvent &event);

        bool isRecordingWake = false;
        bool isRecordingNonWake = false;
        boost::process::opstream recorderInput;
        std::unique_ptr<boost::process::child> recorder = std::make_unique<boost::process::child>(
                    "python3 ./Precise/record.py",
                    boost::process::std_in < recorderInput);

        boost::process::opstream &listenerInput;
        boost::process::ipstream &listenerOutput;
        bool &isNormalListenerRunning;
        bool &isSafeListenerRunning;
        std::unique_ptr<boost::process::child> &listener;
        bool showVisual;
	};
}
#endif // __VoiceDialog__
