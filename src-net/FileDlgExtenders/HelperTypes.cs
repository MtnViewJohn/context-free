//  Copyright (c) 2006, Gustavo Franco
//  Copyright © Decebal Mihailescu 2007
//  Email:  dmihailescu@hotmail.com
//  Email:  gustavo_franco@hotmail.com
//  All rights reserved.

//  Redistribution and use in source and binary forms, with or without modification, 
//  are permitted provided that the following conditions are met:

//  Redistributions of source code must retain the above copyright notice, 
//  this list of conditions and the following disclaimer. 
//  Redistributions in binary form must reproduce the above copyright notice, 
//  this list of conditions and the following disclaimer in the documentation 
//  and/or other materials provided with the distribution. 

//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE. IT CAN BE DISTRIBUTED FREE OF CHARGE AS LONG AS THIS HEADER 
//  REMAINS UNCHANGED.

using System;
using System.IO;
using System.Text;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;
using Win32Types;

namespace FileDialogExtenders
{
    public partial class FileDialogControlBase
    {
        #region Helper Classes
        
        private class NativeFileDialogWrapper : NativeWindow, IDisposable
        {
            public const SetWindowPosFlags UFLAGSSIZE =
                SetWindowPosFlags.SWP_NOACTIVATE |
                SetWindowPosFlags.SWP_NOOWNERZORDER |
                SetWindowPosFlags.SWP_NOMOVE;
            #region Delegates

            #endregion

            #region Events
            #endregion

            #region Variables Declaration
            private int _filterIndex;
            private FileDialogControlBase _CustomCtrl;
            #endregion

            #region Constructors
            public NativeFileDialogWrapper(FileDialogControlBase fd)
            {
                _CustomCtrl = fd;
                if (_CustomCtrl != null)
                    fd.MSDialog.Disposed += new EventHandler(NativeDialogWrapper_Disposed);

            }

            void NativeDialogWrapper_Disposed(object sender, EventArgs e)
            {
                Dispose();
            }
            #endregion

            #region Methods
            public void Dispose()
            {
                //ReleaseHandle();
                if (_CustomCtrl != null && _CustomCtrl.MSDialog != null)
                {
                    _CustomCtrl.MSDialog.Disposed -= new EventHandler(NativeDialogWrapper_Disposed);
                    _CustomCtrl.MSDialog.Dispose();
                    if (_CustomCtrl != null)
                        _CustomCtrl.MSDialog = null;
                }
                if (_CustomCtrl != null)
                {
                    _CustomCtrl.Dispose();
                    _CustomCtrl = null;
                }

                DestroyHandle();
            }
            #endregion

            #region Overrides
            protected override void WndProc(ref Message m)
            {
                switch ((Msg)m.Msg)
                {
                    case Msg.WM_NOTIFY:
                        OFNOTIFY ofNotify = (OFNOTIFY)Marshal.PtrToStructure(m.LParam, typeof(OFNOTIFY));
                        switch (ofNotify.hdr.code)
                        {
                            case (uint)DialogChangeStatus.CDN_SELCHANGE:
                                {
                                    StringBuilder filePath = new StringBuilder(256);
                                    NativeMethods.SendMessage(new HandleRef(this, NativeMethods.GetParent(Handle)), (uint)DialogChangeProperties.CDM_GETFILEPATH, (IntPtr)256, filePath);
                                    if (_CustomCtrl != null)
                                        _CustomCtrl.OnFileNameChanged(this, filePath.ToString());
                                }
                                break;
                            case (uint)DialogChangeStatus.CDN_FOLDERCHANGE:
                                {
                                    StringBuilder folderPath = new StringBuilder(256);
                                    NativeMethods.SendMessage(new HandleRef(this, NativeMethods.GetParent(Handle)), (int)DialogChangeProperties.CDM_GETFOLDERPATH, (IntPtr)256, folderPath);
                                    if (_CustomCtrl != null)
                                        _CustomCtrl.OnFolderNameChanged(this, folderPath.ToString());
                                }
                                break;
                            case (uint)DialogChangeStatus.CDN_TYPECHANGE:
                                {
                                    OPENFILENAME ofn = (OPENFILENAME)Marshal.PtrToStructure(ofNotify.OpenFileName, typeof(OPENFILENAME));
                                    int i = ofn.nFilterIndex;
                                    if (_CustomCtrl != null && _filterIndex != i)
                                    {
                                        _filterIndex = i;
                                        _CustomCtrl.OnFilterChanged(this as IWin32Window, i);
                                    }
                                }
                                break;
                            case (uint)DialogChangeStatus.CDN_INITDONE:
                                break;
                            case (uint)DialogChangeStatus.CDN_SHAREVIOLATION:
                                break;
                            case (uint)DialogChangeStatus.CDN_HELP:
                                break;
                            case (uint)DialogChangeStatus.CDN_INCLUDEITEM:
                                break;

                            case (uint)DialogChangeStatus.CDN_FILEOK://0xfffffda2:
#pragma warning disable 1690, 0414
                                NativeMethods.SetWindowPos(_CustomCtrl._hFileDialogHandle, IntPtr.Zero,
                                (int)_CustomCtrl._OpenDialogWindowRect.left,
                                (int)_CustomCtrl._OpenDialogWindowRect.top,
                                (int)_CustomCtrl._OpenDialogWindowRect.Width,
                                (int)_CustomCtrl._OpenDialogWindowRect.Height,
                                FileDialogControlBase.NativeFileDialogWrapper.UFLAGSSIZE);
                                break;
#pragma warning restore 1690, 0414
                            default: 
                                break;

                        }
                        break;
                    case Msg.WM_COMMAND:
                        switch (NativeMethods.GetDlgCtrlID(m.LParam))//switch (m.WParam & 0x0000ffff)
                        {
                            case (int)ControlsId.ButtonOk://OK
                                break;
                            case (int)ControlsId.ButtonCancel://Cancel
                                break;
                            case (int)ControlsId.ButtonHelp:  //0x0000040e://help
                                break;
                        }
                        break;
                }
                base.WndProc(ref m);
            }
            #endregion
        }

    private class DialogWrapper<FDLG> : NativeWindow, IDisposable 
        where FDLG : FileDialog, new() 
    {
        #region Constants Declaration
        private const SetWindowPosFlags UFLAGSSIZEEX =
            SetWindowPosFlags.SWP_NOACTIVATE |
            SetWindowPosFlags.SWP_NOOWNERZORDER |
            SetWindowPosFlags.SWP_NOMOVE |
            SetWindowPosFlags.SWP_ASYNCWINDOWPOS |
            SetWindowPosFlags.SWP_DEFERERASE;
        private const SetWindowPosFlags UFLAGSMOVE =
            SetWindowPosFlags.SWP_NOACTIVATE |
            SetWindowPosFlags.SWP_NOOWNERZORDER |
            SetWindowPosFlags.SWP_NOSIZE;
        private const SetWindowPosFlags UFLAGSHIDE =
            SetWindowPosFlags.SWP_NOACTIVATE |
            SetWindowPosFlags.SWP_NOOWNERZORDER |
            SetWindowPosFlags.SWP_NOMOVE |
            SetWindowPosFlags.SWP_NOSIZE |
            SetWindowPosFlags.SWP_HIDEWINDOW;
        private const SetWindowPosFlags UFLAGSZORDER =
            SetWindowPosFlags.SWP_NOACTIVATE |
            SetWindowPosFlags.SWP_NOMOVE |
            SetWindowPosFlags.SWP_NOSIZE;
        const uint WS_VISIBLE = 0x10000000;
        static readonly IntPtr HWND_MESSAGE = new IntPtr(-3);
        static readonly IntPtr NULL = IntPtr.Zero;
        #endregion

        #region Variables Declaration
        IntPtr _hDummyWnd = NULL;
        private FileDialogControlBase _CustomControl = null;
        private bool _WatchForActivate = false;
        private Size mOriginalSize;
        private IntPtr _hFileDialogHandle;
        private WINDOWINFO _ListViewInfo;
        private NativeFileDialogWrapper _BaseDialogNative;
        private IntPtr _ComboFolders;
        private WINDOWINFO _ComboFoldersInfo;
        private IntPtr _hGroupButtons;
        private WINDOWINFO _GroupButtonsInfo;
        private IntPtr _hComboFileName;
        private WINDOWINFO _ComboFileNameInfo;
        private IntPtr _hComboExtensions;
        private WINDOWINFO _ComboExtensionsInfo;
        IntPtr _hOKButton;
        WINDOWINFO _OKButtonInfo;
        private IntPtr _hCancelButton;
        private WINDOWINFO _CancelButtonInfo;
        private IntPtr _hHelpButton;
        private WINDOWINFO _HelpButtonInfo;
        private IntPtr _hToolBarFolders;
        private WINDOWINFO _ToolBarFoldersInfo;
        private IntPtr _hLabelFileName;
        private WINDOWINFO _LabelFileNameInfo;
        private IntPtr _hLabelFileType;
        private WINDOWINFO _LabelFileTypeInfo;
        private IntPtr _hChkReadOnly;
        private WINDOWINFO _ChkReadOnlyInfo;
        private bool mIsClosing = false;
        private bool mInitializated = false;
        private RECT _DialogWindowRect = new RECT();
        private RECT _DialogClientRect = new RECT();

        #endregion

        #region Constructors

        public DialogWrapper(FileDialogControlBase fileDialogEx)
        {
            //create the FileDialog &  custom control without UI yet
            _CustomControl = fileDialogEx;
            _CustomControl.MSDialog = new FDLG();
            AssignDummyWindow();
            _WatchForActivate = true;

        }
        #endregion

        #region Events

        #endregion

        #region Methods

        private void AssignDummyWindow()
        {
            //_hDummyWnd = Win32.CreateWindowEx(0x00050100, "Message", null, 0x16C80000, -10000, -10000, 0, 0,
            //parent.Handle, NULL, NULL, NULL);
                _hDummyWnd = NativeMethods.CreateWindowEx(0, "Message", null, WS_VISIBLE, 0, 0, 0, 0,
                HWND_MESSAGE, NULL, NULL, NULL);
            if (_hDummyWnd == NULL || !NativeMethods.IsWindow(_hDummyWnd))
                throw new ApplicationException("Unable to create a dummy window");
            AssignHandle(_hDummyWnd);
        }


        public void Dispose()
        {
            //ReleaseHandle();
            if (_CustomControl != null &&_CustomControl.MSDialog != null)
            {
                _CustomControl.MSDialog.Disposed -= new EventHandler(DialogWrappper_Disposed);
                _CustomControl.MSDialog.Dispose();
                _CustomControl.MSDialog = null;
            }
            if (_CustomControl!= null)
            {
                _CustomControl.Disposed -= new EventHandler(DialogWrappper_Disposed);
                _CustomControl.Dispose();
                _CustomControl = null;
            }
            if (_BaseDialogNative != null)
            {
                _BaseDialogNative.Dispose();
                _BaseDialogNative = null;
            }
            NativeMethods.DestroyWindow(_hDummyWnd);
            DestroyHandle();
        }
        #endregion

        #region Private Methods
        private void PopulateWindowsHandlers()
        {
            NativeMethods.EnumChildWindows(_hFileDialogHandle, new NativeMethods.EnumWindowsCallBack(FileDialogEnumWindowCallBack), 0);
        }

        private bool FileDialogEnumWindowCallBack(IntPtr hwnd, int lParam)
        {
            StringBuilder className = new StringBuilder(256);
            NativeMethods.GetClassName(hwnd, className, className.Capacity);
            int controlID = NativeMethods.GetDlgCtrlID(hwnd);
            WINDOWINFO windowInfo;
            NativeMethods.GetWindowInfo(hwnd, out windowInfo);

            // Dialog Window
            if (className.ToString().StartsWith("#32770"))
            {
                _BaseDialogNative = new NativeFileDialogWrapper(_CustomControl);
                _BaseDialogNative.AssignHandle(hwnd);
                return true;
            }

            switch ((ControlsId)controlID)
            {
                case ControlsId.DefaultView:
                    _CustomControl._hListViewPtr = hwnd;
                    NativeMethods.GetWindowInfo(hwnd, out _ListViewInfo);
                    _CustomControl.UpdateListView();
                    break;
                case ControlsId.ComboFolder:
                    _ComboFolders = hwnd;
                    _ComboFoldersInfo = windowInfo;
                    break;
                case ControlsId.ComboFileType:
                    _hComboExtensions = hwnd;
                    _ComboExtensionsInfo = windowInfo;
                    break;
                case ControlsId.ComboFileName:
                    if (className.ToString().ToLower() == "comboboxex32")
                    {
                        _hComboFileName = hwnd;
                        _ComboFileNameInfo = windowInfo;
                    }
                    break;
                case ControlsId.GroupFolder:
                    _hGroupButtons = hwnd;
                    _GroupButtonsInfo = windowInfo;
                    break;
                case ControlsId.LeftToolBar:
                    _hToolBarFolders = hwnd;
                    _ToolBarFoldersInfo = windowInfo;
                    break;
                case ControlsId.ButtonOk:
                    _hOKButton = hwnd;
                    _OKButtonInfo = windowInfo;
                    _CustomControl._hOKButton = hwnd;
                    //Win32Types.NativeMethods.EnableWindow(_hOKButton, false);
                    break;
                case ControlsId.ButtonCancel:
                    _hCancelButton = hwnd;
                    _CancelButtonInfo = windowInfo;
                    break;
                case ControlsId.ButtonHelp:
                    _hHelpButton = hwnd;
                    _HelpButtonInfo = windowInfo;
                    break;
                case ControlsId.CheckBoxReadOnly:
                    _hChkReadOnly = hwnd;
                    _ChkReadOnlyInfo = windowInfo;
                    break;
                case ControlsId.LabelFileName:
                    _hLabelFileName = hwnd;
                    _LabelFileNameInfo = windowInfo;
                    break;
                case ControlsId.LabelFileType:
                    _hLabelFileType = hwnd;
                    _LabelFileTypeInfo = windowInfo;
                    break;
            }

            return true;
        }

        private void InitControls()
        {
            mInitializated = true;

            // Lets get information about the current open dialog
            NativeMethods.GetClientRect(_hFileDialogHandle, ref _DialogClientRect);
            NativeMethods.GetWindowRect(_hFileDialogHandle, ref _DialogWindowRect);

            // Lets borrow the Handles from the open dialog control
            PopulateWindowsHandlers();

            switch (_CustomControl.FileDlgStartLocation)
            {
                case AddonWindowLocation.Right:
                    // Now we transfer the control to the open dialog
                    _CustomControl.Location = new Point((int)(_DialogClientRect.Width - _CustomControl.Width), 0);
                    break;
                case AddonWindowLocation.Bottom:
                    // Now we transfer the control to the open dialog
                    _CustomControl.Location = new Point(0, (int)(_DialogClientRect.Height - _CustomControl.Height));
                    break;
                case AddonWindowLocation.BottomRight:
                    // We don't have to do too much in this case, just the default thing
                    _CustomControl.Location = new Point((int)(_DialogClientRect.Width - _CustomControl.Width), (int)(_DialogClientRect.Height - _CustomControl.Height));
                    break;
            }
            // Everything is ready, now lets change the parent
            NativeMethods.SetParent(_CustomControl.Handle, _hFileDialogHandle);

            // Send the control to the back
            NativeMethods.SetWindowPos(_CustomControl.Handle, (IntPtr)ZOrderPos.HWND_BOTTOM, 0, 0, 0, 0, UFLAGSZORDER);
            _CustomControl.MSDialog.Disposed += new EventHandler(DialogWrappper_Disposed);
        }

        void DialogWrappper_Disposed(object sender, EventArgs e)
        {
            Dispose();
        }
        #endregion

        #region Overrides
        protected override void WndProc(ref Message m)
        {
            switch ((Msg)m.Msg)
            {
                case Msg.WM_SHOWWINDOW:
                    mInitializated = true;
                    InitControls();
                    break;
                case Msg.WM_SIZING:
                    RECT currentSize = new RECT();
                    NativeMethods.GetClientRect(_hFileDialogHandle, ref currentSize);
                    switch (_CustomControl.FileDlgStartLocation)
                    {
                        case AddonWindowLocation.Right:
                            if (currentSize.Height != _CustomControl.Height)
                                NativeMethods.SetWindowPos(_CustomControl.Handle, (IntPtr)ZOrderPos.HWND_BOTTOM, 0, 0, (int)_CustomControl.Width, (int)currentSize.Height, UFLAGSSIZEEX);
                            break;
                        case AddonWindowLocation.Bottom:
                            if (currentSize.Height != _CustomControl.Height)
                                NativeMethods.SetWindowPos(_CustomControl.Handle, (IntPtr)ZOrderPos.HWND_BOTTOM, 0, 0, (int)currentSize.Width, (int)_CustomControl.Height, UFLAGSSIZEEX);
                            break;
                        case AddonWindowLocation.BottomRight:
                            if (currentSize.Width != _CustomControl.Width || currentSize.Height != _CustomControl.Height)
                                NativeMethods.SetWindowPos(_CustomControl.Handle, (IntPtr)ZOrderPos.HWND_BOTTOM, (int)currentSize.Width, (int)currentSize.Height, (int)currentSize.Width, (int)currentSize.Height, UFLAGSSIZEEX);
                            break;
                    }
                    break;
                case Msg.WM_WINDOWPOSCHANGING:
                    if (!mIsClosing)
                    {
                        if (!mInitializated)
                        {
                            // Resize OpenDialog to make fit our extra form
                            WINDOWPOS pos = (WINDOWPOS)Marshal.PtrToStructure(m.LParam, typeof(WINDOWPOS));
                            if (pos.flags != 0 && ((pos.flags & (int)SWP_Flags.SWP_NOSIZE) != (int)SWP_Flags.SWP_NOSIZE))
                            {
                                switch (_CustomControl.FileDlgStartLocation)
                                {
                                    case AddonWindowLocation.Right:
                                        mOriginalSize = new Size(pos.cx, pos.cy);

                                        pos.cx += _CustomControl.Width;
                                        Marshal.StructureToPtr(pos, m.LParam, true);

                                        currentSize = new RECT();
                                        NativeMethods.GetClientRect(_hFileDialogHandle, ref currentSize);
                                        _CustomControl.Height = (int)currentSize.Height;
                                        break;

                                    case AddonWindowLocation.Bottom:
                                        mOriginalSize = new Size(pos.cx, pos.cy);

                                        pos.cy += _CustomControl.Height;
                                        Marshal.StructureToPtr(pos, m.LParam, true);

                                        currentSize = new RECT();
                                        NativeMethods.GetClientRect(_hFileDialogHandle, ref currentSize);
                                        _CustomControl.Width = (int)currentSize.Width;
                                        break;

                                    case AddonWindowLocation.BottomRight:
                                        mOriginalSize = new Size(pos.cx, pos.cy);

                                        pos.cy += _CustomControl.Height;
                                        pos.cx += _CustomControl.Width;
                                        Marshal.StructureToPtr(pos, m.LParam, true);

                                        break;
                                }
                            }
                        }
                    }
                    break;
                case Msg.WM_IME_NOTIFY:
                    if (m.WParam == (IntPtr)ImeNotify.IMN_CLOSESTATUSWINDOW)
                    {
                        mIsClosing = true;
                        NativeMethods.SetWindowPos(_hFileDialogHandle, IntPtr.Zero, 0, 0, 0, 0, UFLAGSHIDE);
                        NativeMethods.GetWindowRect(_hFileDialogHandle, ref _DialogWindowRect);
                        NativeMethods.SetWindowPos(_hFileDialogHandle, IntPtr.Zero,
                            (int)(_DialogWindowRect.left),
                            (int)(_DialogWindowRect.top),
                            (int)(mOriginalSize.Width),
                            (int)(mOriginalSize.Height),
                            FileDialogControlBase.NativeFileDialogWrapper.UFLAGSSIZE);
                    }
                    break;
                case Msg.WM_PAINT:
                    break;

                case Msg.WM_NCCREATE:
                    break;

                case Msg.WM_CREATE:
                    break;

                case Msg.WM_ACTIVATE:
                    if (_WatchForActivate && !mIsClosing && m.Msg == (int)Msg.WM_ACTIVATE)//WM_NCACTIVATE works too
                    {  //Now the Open/Save Dialog is visible and about to enter the modal loop 
                        _WatchForActivate = false;
                        //Now we save the real dialog window handle
                        _hFileDialogHandle = m.LParam;
                        ReleaseHandle();//release the dummy window
                        AssignHandle(_hFileDialogHandle);//assign the native open file handle to grab the messages
#pragma warning disable 0197, 0414
                        NativeMethods.GetWindowRect(_hFileDialogHandle, ref _CustomControl._OpenDialogWindowRect);
#pragma warning restore 0197, 0414
                        _CustomControl._hFileDialogHandle = _hFileDialogHandle;

                    }
                    break;
                case Msg.WM_COMMAND:
                    switch(NativeMethods.GetDlgCtrlID(m.LParam))
                    {
                        case (int)ControlsId.ButtonOk://OK
                            break;
                        case (int)ControlsId.ButtonCancel://Cancel
#pragma warning disable 1690, 0414
                            NativeMethods.SetWindowPos(_CustomControl._hFileDialogHandle, IntPtr.Zero,
                            (int)_CustomControl._OpenDialogWindowRect.left,
                            (int)_CustomControl._OpenDialogWindowRect.top,
                            (int)_CustomControl._OpenDialogWindowRect.Width,
                            (int)_CustomControl._OpenDialogWindowRect.Height,
                            FileDialogControlBase.NativeFileDialogWrapper.UFLAGSSIZE);
#pragma warning restore 1690, 0414
                            break;
                        case (int)ControlsId.ButtonHelp://help
                            break;
                        case 0:
                            break;
                        default:
                            break;
                    }//switch(NativeMethods.GetDlgCtrlID(m.LParam)) ends
                    break;
                default:
                    break;
            }//switch ((Msg)m.Msg) ends
            base.WndProc(ref m);
        }       
        #endregion
        #region Properties
        #endregion
    }
    #endregion
    }

    #region Enums
    public enum AddonWindowLocation
    {
        BottomRight = 0,
        Right = 1,
        Bottom = 2
    }

    internal enum ControlsId :int
    {
        ButtonOk = 0x1,
        ButtonCancel = 0x2,
        ButtonHelp = 0x40E,//0x0000040e
        GroupFolder = 0x440,
        LabelFileType = 0x441,
        LabelFileName = 0x442,
        LabelLookIn = 0x443,
        DefaultView = 0x461,
        LeftToolBar = 0x4A0,
        ComboFileName = 0x47c,
        ComboFileType = 0x470,
        ComboFolder = 0x471,
        CheckBoxReadOnly = 0x410
    }
    #endregion

}
