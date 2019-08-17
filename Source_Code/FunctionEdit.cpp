//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FunctionEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFuncEdit *FuncEdit;
TMainForm *MForm;
//---------------------------------------------------------------------------
__fastcall TFuncEdit::TFuncEdit(TComponent* Owner, TMainForm *MFm, int EditPage, int LayerID, int EditFunc, int FuncIndex, int EditEvent)
    : TForm(Owner)
{
    MForm = MFm;
    FuncEdit = this;
    //�ô��ھ���
    FuncEdit->Left = (Screen->Width - FuncEdit->Width) / 2;
    FuncEdit->Top = (Screen->Height - FuncEdit->Height) / 2;
    //FuncEdit->Caption = MForm->UserConfigGetLanguageString(56);
    InitUiLanguage();//��ʼ�������ַ���

    memset(&EditPara, 0x00, sizeof(EditPara));
    EditPara.EditPage = EditPage;
    EditPara.LayerID = LayerID;
    EditPara.EditFunc = EditFunc;
    EditPara.FuncIndex = FuncIndex;
    EditPara.EditEvent = EditEvent;
    GetFuncMap();
}
//---------------------------------------------------------------------------
void	__fastcall TFuncEdit::GetFuncMap(void)//��ȡ��ǰҪ�༭�Ĺ���ӳ��
{
    switch(EditPara.EditPage)
    {
        case _DEF_DEFINE_FUNC_EDIT_ROUTINE_PAGE://���津��ҳ
        {
            EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].NormalKeyConfig.KeyConfig[EditPara.FuncIndex];
            FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) + "[" +
                                String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1005) + "->" + MForm->UserConfigGetLanguageString(1002) + "[" + String(EditPara.FuncIndex) + "]";
            DisableFuncs();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_COMBOKEY_PAGE://��ϼ��༭ҳ
        {
            if(EditPara.EditEvent == _DEF_DEFINE_FUNC_EDIT_PARA1)
            {
                EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].ComboKeyConfig.TrigConfig[EditPara.FuncIndex].DownFuncMap;
                FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) + "[" +
                                    String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1006) +
                                    "->" + MForm->UserConfigGetLanguageString(1003) + "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1011);
            }
            if(EditPara.EditEvent == _DEF_DEFINE_FUNC_EDIT_PARA2)
            {
                EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].ComboKeyConfig.TrigConfig[EditPara.FuncIndex].UpFuncMap;
                FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) +
                                    "[" + String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1006) +
                                    "->" + MForm->UserConfigGetLanguageString(1003) + "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1012);
            }
            DisableFuncs();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_NHITKEY_PAGE://�������༭ҳ
        {
            EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].nHitKeyConfig.TrigConfig[EditPara.FuncIndex].TrigFunc;
            FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) + "[" +
                                String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1007) + "->" + MForm->UserConfigGetLanguageString(1003) +
                                "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1013);
            DisableFuncs();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_NFUNC_PAGE://�๦�ܼ��༭ҳ
        {
            if(EditPara.EditEvent == _DEF_DEFINE_FUNC_EDIT_PARA1)
            {
                EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].nFuncKeyConfig.KeyConfig[EditPara.FuncIndex].ClickTrigFuncMap;
                FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) +
                                    "[" + String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1008) + "->" + MForm->UserConfigGetLanguageString(1003) + "[" +
                                    String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1014);
            }
            if(EditPara.EditEvent == _DEF_DEFINE_FUNC_EDIT_PARA2)
            {
                EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].nFuncKeyConfig.KeyConfig[EditPara.FuncIndex].LongPressFuncMap;
                FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) + "[" +
                                    String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1008) + "->" + MForm->UserConfigGetLanguageString(1003) +
                                    "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1015);
            }
            if(EditPara.EditEvent == _DEF_DEFINE_FUNC_EDIT_PARA3)
            {
                EditPara.KeyMap = &MForm->LayerData[EditPara.LayerID].nFuncKeyConfig.KeyConfig[EditPara.FuncIndex].LongPressUpFuncMap;
                FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1001) +
                                    "[" + String(EditPara.LayerID) + "]->" + MForm->UserConfigGetLanguageString(1008) +
                                    "->" + MForm->UserConfigGetLanguageString(1003) + "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1016);
            }
            DisableFuncs();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_KEYLOCK_PAGE://�������༭��
        {
            EditPara.KeyLockCode = &MForm->KeyLockData.Group[EditPara.FuncIndex].KeyCode[EditPara.EditEvent];
            FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1009) +
                                "->" + MForm->UserConfigGetLanguageString(1003) + "[" + String(EditPara.FuncIndex) + "]" + MForm->UserConfigGetLanguageString(1002) +
                                "[" + String(EditPara.EditEvent + 1) + "]";
            DisableFuncs();
            TabSheet3->TabVisible = false;
            TabSheet4->TabVisible = false;
            TabSheet5->TabVisible = false;
            TabSheet7->TabVisible = false;

        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_MACRO_PAGE://��༭��
        {
            EditPara.KeyMap = &MForm->MacroData[EditPara.LayerID].MacroStep[EditPara.FuncIndex];
            FuncEdit->Caption = MForm->UserConfigGetLanguageString(1000) + "->" + MForm->UserConfigGetLanguageString(1010) +
                                "->" + MForm->UserConfigGetLanguageString(1003) + "[" + String(EditPara.LayerID) + "]" + MForm->UserConfigGetLanguageString(1004) + "[" +
                                String(EditPara.FuncIndex) + "]";
        }
    }


    //��ʼ����������
    int index;
    TListItem *item;
    //��ý�����
    for(index = 0; index < MForm->USBHidCode.MediaCode->Count; index++)
    {
        item = LV_MediaKeyCodeSelect->Items->Add();
        item->Caption = MForm->USBHidCode.MediaCode->Strings[index];
        item->SubItems->Add(MForm->USBHidCode.MediaString->Strings[index]);
    }
    //��ͨ��������
    for(index = 0; index < MForm->USBHidCode.kbString->Count; index++)
    {
        item = LV_NormalKeyCodeSelect->Items->Add();
        item->SubItems->Add(MForm->USBHidCode.kbString->Strings[index]);
        item->Caption = MForm->USBHidCode.KbCode->Strings[index];
    }

    //�㿪�أ���ѡ��
    for(index = 0; index < _DEF_DEFINE_TRIG_LAYER_COUNT; index++)
    {
        ComboBox_LayerEnable_LayerSelect->Items->Add(MForm->UserConfigGetLanguageString(1017) + "[" + String(index) + "]");
    }
    ComboBox_LayerEnable_LayerSelect->ItemIndex = 0;

    //������Ϊ������ȼ�
    for(index = 0; index < _DEF_DEFINE_TRIG_LAYER_COUNT; index++)
    {
        ComboBox_LayerTopPrio_LayerSelect->Items->Add(MForm->UserConfigGetLanguageString(1017) + "[" + String(index) + "]");
    }
    ComboBox_LayerTopPrio_LayerSelect->ItemIndex = 0;

    //�ƶ�������ȼ�
    for(index = 0; index < _DEF_DEFINE_TRIG_LAYER_COUNT; index++)
    {
        ComboBox_LayerPrioMove_LayerSelect->Items->Add(MForm->UserConfigGetLanguageString(1017) + "[" + String(index) + "]");
    }
    ComboBox_LayerPrioMove_LayerSelect->ItemIndex = 0;

    //�����ѡ��
    for(index = 0; index < _DEF_DEFINE_MACRO_MAX_GROUP; index++)
    {
        ComboBox_MacroLoad_Select->Items->Add(MForm->UserConfigGetLanguageString(1018) + "[" + String(index) + "]");
    }
    ComboBox_MacroLoad_Select->ItemIndex = 0;

    //��Ĳ�ѡ��
    for(index = 0; index < _DEF_DEFINE_MACRO_GROUP_MAX_STEP; index++)
    {
        ComboBox_MacroLoad_Select_Step->Items->Add(MForm->UserConfigGetLanguageString(1019) + "[" + String(index) + "]");
    }
    ComboBox_MacroLoad_Select_Step->ItemIndex = 0;


    //����������ѡ��
    for(index = 0; index < _DEF_DEFINE_LOCK_KEY_MAX_GROUP; index++)
    {
        ComboBox_KeyLock_Select->Items->Add(MForm->UserConfigGetLanguageString(1020) + "[" + String(index) + "]");
    }
    ComboBox_KeyLock_Select->ItemIndex = 0;


    //�걾������ת
    for(index = 0; index < _DEF_DEFINE_MACRO_GROUP_MAX_STEP; index++)
    {
        ComboBox_MacroJmp->Items->Add(index);
    }
    ComboBox_MacroJmp->ItemIndex = 0;

    //�������ת
    for(index = 0; index < _DEF_DEFINE_MACRO_MAX_GROUP; index++)
    {
        ComboBox_MacroGroupJmp_GroupSelect->Items->Add(index);
    }
    ComboBox_MacroGroupJmp_GroupSelect->ItemIndex = 0;

    //�������ת-��
    for(index = 0; index < _DEF_DEFINE_MACRO_GROUP_MAX_STEP; index++)
    {
        ComboBox_MacroGroupJmp_StepSelect->Items->Add(index);
    }
    ComboBox_MacroGroupJmp_StepSelect->ItemIndex = 0;
}

void __fastcall TFuncEdit::LV_NormalKeyCodeSelectDblClick(TObject *Sender)
{
    //��ͨ����ѡ��
    if(LV_NormalKeyCodeSelect->Selected == NULL) return;

    switch(EditPara.EditPage)
    {
        case _DEF_DEFINE_FUNC_EDIT_KEYLOCK_PAGE://�������༭��
        {
            if(LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00) == 0x00)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            WORD Code = LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x0000);
            *EditPara.KeyLockCode = Code;
            FuncEdit->Close();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_MACRO_PAGE://��༭ҳ
        {
            if(LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00) == 0x00)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));


            if(RadioButton_Macro_NormalKey->Checked == true)//����������������
            {
                EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_FUNC_NORMAL_KEY;
                EditPara.KeyMap->NormalKey.index = LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00);
            }
            else
            {
                if(RadioButton_Macro_Normal_Down->Checked == true)//ֻ������¼���
                {
                    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_MACRO_OUT_NORMAL_KEY_PRESS;
                    EditPara.KeyMap->MacroOutNormalKeyPress.KeyCode = LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00);
                }
                else
                {
                    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_MACRO_OUT_NORMAL_KEY_UP; //ֻ���̧�����
                    EditPara.KeyMap->MacroOutNormalKeyUp.KeyCode = LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00);
                }
            }
            FuncEdit->Close();
        }
        break;
        default:
        {
            if(LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00) == 0x00)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
            EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_FUNC_NORMAL_KEY;
            EditPara.KeyMap->NormalKey.index = LV_NormalKeyCodeSelect->Selected->Caption.ToIntDef(0x00);
            FuncEdit->Close();
        }
    }


}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::LV_MediaKeyCodeSelectDblClick(TObject *Sender)
{
    //��ý�����ѡ��
    if(LV_MediaKeyCodeSelect->Selected == NULL) return;

    switch(EditPara.EditPage)
    {
        case _DEF_DEFINE_FUNC_EDIT_KEYLOCK_PAGE://�������༭��
        {
            if(LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000) == 0x0000)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            WORD Code = LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000) | 0x8000;
            *EditPara.KeyLockCode = Code;
            FuncEdit->Close();
        }
        break;
        case _DEF_DEFINE_FUNC_EDIT_MACRO_PAGE://��༭ҳ
        {
            if(LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000) == 0x0000)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));

            if(RadioButton_Macro_Media_NormalOut->Checked == true)
            {
                EditPara.KeyMap->MediaKey.FuncID = _DEF_DEFINE_FUNC_MEDIA_KEY;//���������ý�����
                EditPara.KeyMap->MediaKey.MediaKeyIndex = LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000);
            }
            else
            {
                if(RadioButton_Macro_Media_Down->Checked == true)
                {
                    EditPara.KeyMap->MacroOutMediaKeyPress.FuncID = _DEF_DEFINE_MACRO_OUT_MEDIA_KEY_PRESS;//ֻ������¼���
                    EditPara.KeyMap->MacroOutMediaKeyPress.MediaKeyCode = LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000);
                }
                else
                {
                    EditPara.KeyMap->MacroOutMediaKeyUp.FuncID = _DEF_DEFINE_MACRO_OUT_MEDIA_KEY_UP;//ֻ���̧�����
                    EditPara.KeyMap->MacroOutMediaKeyUp.MediaKeyCode = LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000);
                }
            }
            FuncEdit->Close();
        }
        break;

        default:
        {
            if(LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000) == 0x0000)
            {
                ShowMessage(MForm->UserConfigGetLanguageString(1021));
                return;
            }
            memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
            EditPara.KeyMap->MediaKey.FuncID = _DEF_DEFINE_FUNC_MEDIA_KEY;
            EditPara.KeyMap->MediaKey.MediaKeyIndex = LV_MediaKeyCodeSelect->Selected->Caption.ToIntDef(0x0000);
            FuncEdit->Close();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_LayerEnable_AddClick(TObject *Sender)
{
    //�㿪������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->LayerEnable.FuncID = _DEF_DEFINE_FUNC_LAYER_ENABLE;
    EditPara.KeyMap->LayerEnable.LayerID = ComboBox_LayerEnable_LayerSelect->ItemIndex;

    if(RadioButton_LayerOpen->Checked)
    {
        EditPara.KeyMap->LayerEnable.Enable = true;
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_LayerSetTopPrio_AddClick(TObject *Sender)
{
    //ĳ������Ϊ������ȼ�
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->LayerSetTopPrio.FuncID = _DEF_DEFINE_FUNC_LAYER_SET_TOP_PRIO;
    EditPara.KeyMap->LayerSetTopPrio.LayerID = ComboBox_LayerTopPrio_LayerSelect->ItemIndex;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_LayerPrioMove_AddClick(TObject *Sender)
{
    //�ƶ�����������ȼ�
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->LayerMovePrio.FuncID = _DEF_DEFINE_FUNC_LAYER_MOVE_PRIO;
    EditPara.KeyMap->LayerMovePrio.LayerID = ComboBox_LayerPrioMove_LayerSelect->ItemIndex;

    if(RadioButton_DownPrio->Checked)
    {
        EditPara.KeyMap->LayerEnable.Enable = true; //1=�������ȼ�
    }
    FuncEdit->Close();

}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button1Click(TObject *Sender)
{
    //FN������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->KeyScanFnKeyEnable.FuncID = _DEF_DEFINE_FUNC_KEYSCAN_FN_KEY_ENABLE;

    if(RadioButton2->Checked)
    {
        EditPara.KeyMap->KeyScanFnKeyEnable.Enable = true;
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------


void __fastcall TFuncEdit::Button2Click(TObject *Sender)
{
    //���津������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->KeyScanNormalKeyEnable.FuncID = _DEF_DEFINE_FUNC_KEYSCAN_NORMAL_KEY_ENABLE;

    if(RadioButton3->Checked)
    {
        EditPara.KeyMap->KeyScanNormalKeyEnable.Enable = true;//1=��ֹ����
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button3Click(TObject *Sender)
{
    //��ϼ���������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->KeyScanComboKeyEnable.FuncID = _DEF_DEFINE_FUNC_KEYSCAN_COMBO_KEY_ENABLE;

    if(RadioButton6->Checked)
    {
        EditPara.KeyMap->KeyScanComboKeyEnable.Enable = true;
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button4Click(TObject *Sender)
{
    //��������������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->KeyScannHitKeyEnable .FuncID = _DEF_DEFINE_FUNC_KEYSCAN_NHIT_KEY_ENABLE;

    if(RadioButton8->Checked)
    {
        EditPara.KeyMap->KeyScannHitKeyEnable.Enable = true;
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button5Click(TObject *Sender)
{
    //�๦�ܼ���������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->KeyScannFuncKeyEnable.FuncID = _DEF_DEFINE_FUNC_KEYSCAN_NFUNC_KEY_ENABLE;

    if(RadioButton10->Checked)
    {
        EditPara.KeyMap->KeyScannFuncKeyEnable.Enable = true;
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button6Click(TObject *Sender)
{
    //�����
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->MacroLoad.FuncID = _DEF_DEFINE_FUNC_MACRO_LOAD;
    EditPara.KeyMap->MacroLoad.GroupID = ComboBox_MacroLoad_Select->ItemIndex;
    EditPara.KeyMap->MacroLoad.StepID =  ComboBox_MacroLoad_Select_Step->ItemIndex;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button7Click(TObject *Sender)
{
    //��ֹͣ����
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->MacroStopRun.FuncID = _DEF_DEFINE_MACRO_STOP_MACRO;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button8Click(TObject *Sender)
{
    //����������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->Func_KeyLock.FuncID = _DEF_DEFINE_FUNC_KEY_LOCK;
    EditPara.KeyMap->Func_KeyLock.GroupID = ComboBox_KeyLock_Select->ItemIndex;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------
void	__fastcall TFuncEdit::DisableFuncs(void)//ȡ��һЩ����
{
    TabSheet6->TabVisible = false;
    LV_NormalKeyCodeSelect->Align = alClient;
    LV_MediaKeyCodeSelect->Align = alClient;
    RadioButton_Macro_Normal_Down->Visible = false;
    RadioButton_Macro_Normal_Up->Visible = false;
    RadioButton_Macro_Media_Down->Visible = false;
    RadioButton_Macro_Media_Up->Visible = false;
    RadioButton_Macro_NormalKey->Visible = false;
    RadioButton_Macro_Media_NormalOut->Visible = false;
}

void __fastcall TFuncEdit::Button_MacroJmpAddClick(TObject *Sender)
{
    //�꣬��ת�������ĳһ��ִ��
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->MacroJmpStep.FuncID = _DEF_DEFINE_MACRO_CURR_GROUP_JMP;
    EditPara.KeyMap->MacroJmpStep.StepID = ComboBox_MacroJmp->ItemIndex;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_MacroGroupJmp_ADDClick(TObject *Sender)
{
    //�꣬�����ת
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->MacroJmpGroup.FuncID = _DEF_DEFINE_MACRO_JMP_GROUP;
    EditPara.KeyMap->MacroJmpGroup.GroupID = ComboBox_MacroGroupJmp_GroupSelect->ItemIndex;
    EditPara.KeyMap->MacroJmpGroup.StepID = ComboBox_MacroGroupJmp_StepSelect->ItemIndex;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------


void __fastcall TFuncEdit::Edit1KeyPress(TObject *Sender, wchar_t &Key)
{
    if(Key != VK_BACK && (Key < '0' || Key > '9'))
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_Macro_Delay_AddClick(TObject *Sender)
{
    //������ʱ������
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    if(RadioButton_Macro_InputTime ->Checked == true)
    {
        if(Edit1->Text.ToIntDef(0x00ffffff) > 65535)
        {
            ShowMessage(MForm->UserConfigGetLanguageString(1022));
            return;
        }
        EditPara.KeyMap->MacroDelay.FuncID = _DEF_DEFINE_MACRO_DELAY;
        EditPara.KeyMap->MacroDelay.Timer_L = Edit1->Text.ToIntDef(65535);
    }
    else//�����Ԥ����ʱ��
    {
        EditPara.KeyMap->MacroDelay.FuncID = _DEF_DEFINE_MACRO_DELAY;
        if(RadioButton11->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 100;
        }
        if(RadioButton12->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 200;
        }

        if(RadioButton13->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 300;
        }
        if(RadioButton14->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 500;
        }
        if(RadioButton15->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 800;
        }
        if(RadioButton16->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 1000;
        }
        if(RadioButton17->Checked == true)
        {
            EditPara.KeyMap->MacroDelay.Timer_L = 1500;
        }
    }
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_EffectIndexUpClick(TObject *Sender)
{
    //��һ����Ч
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_BKL_CTL_EFF_INDEX_UP;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------


void __fastcall TFuncEdit::Button_EffectIndexDownClick(TObject *Sender)
{
    //��һ����Ч
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_BKL_CTL_EFF_INDEX_DOWN;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_EffectSpeedUpClick(TObject *Sender)
{
    //�����ٶ�
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_BKL_CTL_EFF_SPEED_UP;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFuncEdit::Button_EffectSpeedDownClick(TObject *Sender)
{
    //����ٶ�
    memset(EditPara.KeyMap, 0x00, sizeof(union _KEYSCAN_ONE_FUNC_MAP_UNION));
    EditPara.KeyMap->NormalKey.FuncID = _DEF_DEFINE_BKL_CTL_EFF_SPEED_DOWN;
    FuncEdit->Close();
}
//---------------------------------------------------------------------------


void	__fastcall TFuncEdit::InitUiLanguage(void)//��ʼ�����������
{
    //������ı�ǩҳ
    TabSheet1->Caption = MForm->UserConfigGetLanguageString(1040);
    TabSheet2->Caption = MForm->UserConfigGetLanguageString(1041);
    TabSheet3->Caption = MForm->UserConfigGetLanguageString(1042);
    TabSheet4->Caption = MForm->UserConfigGetLanguageString(1043);
    TabSheet5->Caption = MForm->UserConfigGetLanguageString(1044);
    TabSheet6->Caption = MForm->UserConfigGetLanguageString(1045);
    TabSheet7->Caption = MForm->UserConfigGetLanguageString(1046);

    //��ͨ����ҳ
    RadioButton_Macro_NormalKey->Caption = MForm->UserConfigGetLanguageString(1050);
    RadioButton_Macro_Normal_Down->Caption = MForm->UserConfigGetLanguageString(1051);
    RadioButton_Macro_Normal_Up->Caption = MForm->UserConfigGetLanguageString(1052);

    LV_NormalKeyCodeSelect->Column[0]->Caption = MForm->UserConfigGetLanguageString(1053);
    LV_NormalKeyCodeSelect->Column[1]->Caption = MForm->UserConfigGetLanguageString(1054);

    //��ý�����ҳ
    RadioButton_Macro_Media_NormalOut->Caption = MForm->UserConfigGetLanguageString(1060);
    RadioButton_Macro_Media_Down->Caption = MForm->UserConfigGetLanguageString(1061);
    RadioButton_Macro_Media_Up->Caption = MForm->UserConfigGetLanguageString(1062);

    LV_MediaKeyCodeSelect->Column[0]->Caption = MForm->UserConfigGetLanguageString(1063);
    LV_MediaKeyCodeSelect->Column[1]->Caption = MForm->UserConfigGetLanguageString(1064);

    //���������
    GroupBox1->Caption = MForm->UserConfigGetLanguageString(1070);
    Label1->Caption = MForm->UserConfigGetLanguageString(1071);
    Label2->Caption = MForm->UserConfigGetLanguageString(1072);
    RadioButton_LayerClose->Caption = MForm->UserConfigGetLanguageString(1073);
    RadioButton_LayerOpen->Caption = MForm->UserConfigGetLanguageString(1074);
    Button_LayerEnable_Add->Caption = MForm->UserConfigGetLanguageString(1075);

    GroupBox2->Caption = MForm->UserConfigGetLanguageString(1080);
    Label3->Caption = MForm->UserConfigGetLanguageString(1081);
    Button_LayerSetTopPrio_Add->Caption = MForm->UserConfigGetLanguageString(1082);

    GroupBox3->Caption = MForm->UserConfigGetLanguageString(1090);
    Label5->Caption = MForm->UserConfigGetLanguageString(1091);
    Label6->Caption = MForm->UserConfigGetLanguageString(1092);
    RadioButton_TopPrio->Caption = MForm->UserConfigGetLanguageString(1093);
    RadioButton_DownPrio->Caption = MForm->UserConfigGetLanguageString(1094);
    Button_LayerPrioMove_Add->Caption = MForm->UserConfigGetLanguageString(1095);

    //��������ҳ
    GroupBox4->Caption = MForm->UserConfigGetLanguageString(1100);
    GroupBox5->Caption = MForm->UserConfigGetLanguageString(1103);
    GroupBox6->Caption = MForm->UserConfigGetLanguageString(1107);
    GroupBox7->Caption = MForm->UserConfigGetLanguageString(1108);
    GroupBox8->Caption = MForm->UserConfigGetLanguageString(1109);

    RadioButton1->Caption = MForm->UserConfigGetLanguageString(1101);
    RadioButton2->Caption = MForm->UserConfigGetLanguageString(1102);

    RadioButton3->Caption = MForm->UserConfigGetLanguageString(1104);
    RadioButton4->Caption = MForm->UserConfigGetLanguageString(1105);

    RadioButton5->Caption = MForm->UserConfigGetLanguageString(1104);
    RadioButton6->Caption = MForm->UserConfigGetLanguageString(1105);

    RadioButton7->Caption = MForm->UserConfigGetLanguageString(1104);
    RadioButton8->Caption = MForm->UserConfigGetLanguageString(1105);

    RadioButton9->Caption = MForm->UserConfigGetLanguageString(1104);
    RadioButton10->Caption = MForm->UserConfigGetLanguageString(1105);

    Button1->Caption = MForm->UserConfigGetLanguageString(1106);
    Button2->Caption = MForm->UserConfigGetLanguageString(1106);
    Button3->Caption = MForm->UserConfigGetLanguageString(1106);
    Button4->Caption = MForm->UserConfigGetLanguageString(1106);
    Button5->Caption = MForm->UserConfigGetLanguageString(1106);


    //���ܵ���ҳ��
    GroupBox9->Caption = MForm->UserConfigGetLanguageString(1120);
    Label4->Caption = MForm->UserConfigGetLanguageString(1121);
    Label8->Caption = MForm->UserConfigGetLanguageString(1122);
    Button6->Caption = MForm->UserConfigGetLanguageString(1123);
    Button7->Caption = MForm->UserConfigGetLanguageString(1124);

    GroupBox10->Caption = MForm->UserConfigGetLanguageString(1125);
    Label7->Caption = MForm->UserConfigGetLanguageString(1126);
    Button8->Caption = MForm->UserConfigGetLanguageString(1127);

    //�깦��ҳ��
    GroupBox11->Caption = MForm->UserConfigGetLanguageString(1130);
    Label9->Caption = MForm->UserConfigGetLanguageString(1131);
    Button_MacroJmpAdd->Caption = MForm->UserConfigGetLanguageString(1132);

    GroupBox12->Caption = MForm->UserConfigGetLanguageString(1140);
    Label10->Caption = MForm->UserConfigGetLanguageString(1141);
    Label11->Caption = MForm->UserConfigGetLanguageString(1142);
    Button_MacroGroupJmp_ADD->Caption = MForm->UserConfigGetLanguageString(1143);

    GroupBox13->Caption = MForm->UserConfigGetLanguageString(1150);
    RadioButton_Macro_InputTime->Caption = MForm->UserConfigGetLanguageString(1151);
    RadioButton11->Caption = MForm->UserConfigGetLanguageString(1152);
    RadioButton12->Caption = MForm->UserConfigGetLanguageString(1153);
    RadioButton13->Caption = MForm->UserConfigGetLanguageString(1154);
    RadioButton14->Caption = MForm->UserConfigGetLanguageString(1155);
    RadioButton15->Caption = MForm->UserConfigGetLanguageString(1156);
    RadioButton16->Caption = MForm->UserConfigGetLanguageString(1157);
    RadioButton17->Caption = MForm->UserConfigGetLanguageString(1158);
    Label12->Caption = MForm->UserConfigGetLanguageString(1159);
    Button_Macro_Delay_Add->Caption = MForm->UserConfigGetLanguageString(1160);

    //�������
    Button_EffectIndexUp->Caption = MForm->UserConfigGetLanguageString(1170);
    Button_EffectIndexDown->Caption = MForm->UserConfigGetLanguageString(1171);

    Button_EffectSpeedUp->Caption = MForm->UserConfigGetLanguageString(1172);
    Button_EffectSpeedDown->Caption = MForm->UserConfigGetLanguageString(1173);
}