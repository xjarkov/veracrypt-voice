#include "System.h"
#include "Main/GraphicUserInterface.h"
#include "ConfirmResetDialog.h"

namespace VeraCrypt
{
    ConfirmResetDialog::ConfirmResetDialog (wxWindow *parent)
        : ConfirmResetDialogBase (parent)
    {
        Layout();
        Fit();
        Center();
    }

    void ConfirmResetDialog::OnOkButtonClick (wxCommandEvent &event)
    {
        int ret;
        ret = system("exec rm -r ./Precise/model/wake-word/*");
        ret = system("exec rm -r ./Precise/model/not-wake-word/*");
        ret = system("exec rm -r ./Precise/model.*");
        //ret = system("exec rm ./Precise/model.net");

        Close();
        //only for supressing warning
        if (ret) {
            return;
        }
    }
}
