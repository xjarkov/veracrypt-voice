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
        VoiceDialog(wxWindow *parent);

    protected:
        void OnWakeRecordButtonClick(wxCommandEvent& event);
        void OnNonWakeRecordButtonClick(wxCommandEvent& event);
        void OnPurgeFilesButtonClick(wxCommandEvent& event);
        void OnTrainModelButtonClick(wxCommandEvent& event);
        void OnStartModelButtonClick(wxCommandEvent& event);

        const wxWindow *parent;
        bool isRecordingWake = false;
        bool isRecordingNonWake = false;
        boost::process::opstream input;
        std::unique_ptr<boost::process::child> recorder = std::make_unique<boost::process::child>(
                    "python3 ./Precise/record.py",
                    boost::process::std_in < input);
	};
}
#endif // __VoiceDialog__
