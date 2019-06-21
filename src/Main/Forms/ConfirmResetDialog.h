#ifndef __ConfirmResetDialog__
#define __ConfirmResetDialog__

#include "Forms.h"
#include "Main/Main.h"

/** Implementing ConfirmResetDialogBase */
namespace VeraCrypt
{
    class ConfirmResetDialog : public ConfirmResetDialogBase
    {
    public:
        ConfirmResetDialog(wxWindow *parent);
        void OnOkButtonClick(wxCommandEvent &event);
    };
}
#endif // __ConfirmResetDialog__
