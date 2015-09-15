﻿// Copyright © 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "Stdafx.h"
#include "Internals/StringUtils.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace CefSharp::Internals;

namespace CefSharp
{
    public ref class CefSettings
    {
    private:
        List<CefCustomScheme^>^ _cefCustomSchemes;
        List<CefExtension^>^ _cefExtensions;
        IDictionary<String^, String^>^ _cefCommandLineArgs;

    internal:
        ::CefSettings* _cefSettings;

    public:
        CefSettings() : _cefSettings(new ::CefSettings())
        {
            _cefSettings->multi_threaded_message_loop = true;
            _cefSettings->no_sandbox = true;
            BrowserSubprocessPath = "CefSharp.BrowserSubprocess.exe";
            _cefCustomSchemes = gcnew List<CefCustomScheme^>();
            _cefExtensions = gcnew List<CefExtension^>();
            _cefCommandLineArgs = gcnew Dictionary<String^, String^>();

            //Automatically discovered and load a system-wide installation of Pepper Flash.
            _cefCommandLineArgs->Add("enable-system-flash", "1");
        }

        !CefSettings()
        {
            delete _cefSettings;
        }

        ~CefSettings()
        {
            this->!CefSettings();
        }

        property IEnumerable<CefCustomScheme^>^ CefCustomSchemes
        {
            IEnumerable<CefCustomScheme^>^ get() { return _cefCustomSchemes; }
        }

        virtual property IEnumerable<CefExtension^>^ Extensions
        {
            IEnumerable<CefExtension^>^ get() { return _cefExtensions; }
        }

        virtual property IDictionary<String^, String^>^ CefCommandLineArgs
        {
            IDictionary<String^, String^>^ get() { return _cefCommandLineArgs; }
        }

        property bool MultiThreadedMessageLoop
        {
            bool get() { return _cefSettings->multi_threaded_message_loop == 1; }
        }

        property String^ BrowserSubprocessPath
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->browser_subprocess_path); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->browser_subprocess_path, value); }
        }

        property String^ CachePath
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->cache_path); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->cache_path, value); }
        }

        /// <summary>
        /// Set to true in order to completely ignore SSL certificate errors.
        /// This is NOT recommended.
        /// </summary>
        property bool IgnoreCertificateErrors
        {
            bool get() { return _cefSettings->ignore_certificate_errors == 1; }
            void set(bool value) { _cefSettings->ignore_certificate_errors = value; }
        }

        property String^ Locale
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->locale); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->locale, value); }
        }

        property String^ LocalesDirPath
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->locales_dir_path); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->locales_dir_path, value); }
        }

        property String^ ResourcesDirPath
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->resources_dir_path); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->resources_dir_path, value); }
        }		

        property String^ LogFile
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->log_file); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->log_file, value); }
        }

        property CefSharp::LogSeverity LogSeverity
        {
            CefSharp::LogSeverity get() { return (CefSharp::LogSeverity)_cefSettings->log_severity; }
            void set(CefSharp::LogSeverity value) { _cefSettings->log_severity = (cef_log_severity_t)value; }
        }

        property bool PackLoadingDisabled
        {
            bool get() { return _cefSettings->pack_loading_disabled == 1; }
            void set(bool value) { _cefSettings->pack_loading_disabled = value; }
        }

        property String^ ProductVersion
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->product_version); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->product_version, value); }
        }

        property int RemoteDebuggingPort
        {
            int get() { return _cefSettings->remote_debugging_port; }
            void set(int value) { _cefSettings->remote_debugging_port = value; }
        }

        property String^ UserAgent
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->user_agent); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->user_agent, value); }
        }

        property bool WindowlessRenderingEnabled
        {
            bool get() { return _cefSettings->windowless_rendering_enabled == 1; }
            void set(bool value) { _cefSettings->windowless_rendering_enabled = value; }
        }

        property bool PersistSessionCookies
        {
            bool get() { return _cefSettings->persist_session_cookies == 1; }
            void set(bool value) { _cefSettings->persist_session_cookies = value; }
        }

        /// <summary>
        /// Comma delimited ordered list of language codes without any whitespace that
        /// will be used in the "Accept-Language" HTTP header. May be set globally
        /// using the CefSettings.AcceptLanguageList value. If both values are
        /// empty then "en-US,en" will be used.
        /// </summary>
        property String^ AcceptLanguageList
        {
            String^ get() { return StringUtils::ToClr(_cefSettings->accept_language_list); }
            void set(String^ value) { StringUtils::AssignNativeFromClr(_cefSettings->accept_language_list, value); }
        }

        /// <summary>
        /// Registers a custom scheme using the provided settings.
        /// </summary>
        /// <param name="cefCustomScheme">The CefCustomScheme which provides the details about the scheme.</param>
        void RegisterScheme(CefCustomScheme^ cefCustomScheme)
        {
            _cefCustomSchemes->Add(cefCustomScheme);
        }

        /// <summary>
        /// Registers an extension with the provided settings.
        /// </summary>
        /// <param name="extension">The CefExtension that contains the extension code.</param>
        void RegisterExtension(CefExtension^ extension)
        {
            if (_cefExtensions->Contains(extension))
            {
                throw gcnew ArgumentException("An extension with the same name is already registered.", "extension");
            }
            _cefExtensions->Add(extension);
        }

        /// <summary>
        /// Set command line arguments for best OSR (Offscreen and WPF) Rendering performance
        /// This will disable WebGL, look at the source to determine which flags best suite
        /// your requirements.
        /// </summary>
        void SetOffScreenRenderingBestPerformanceArgs()
        {
            // If the PDF extension is enabled then cc Surfaces must be disabled for
            // PDFs to render correctly.
            // See https://bitbucket.org/chromiumembedded/cef/issues/1689 for details.
            _cefCommandLineArgs->Add("disable-surfaces", "1");

            // Use software rendering and compositing (disable GPU) for increased FPS
            // and decreased CPU usage. This will also disable WebGL so remove these
            // switches if you need that capability.
            // See https://bitbucket.org/chromiumembedded/cef/issues/1257 for details.
            _cefCommandLineArgs->Add("disable-gpu", "1");
            _cefCommandLineArgs->Add("disable-gpu-compositing", "1");

            // Synchronize the frame rate between all processes. This results in
            // decreased CPU usage by avoiding the generation of extra frames that
            // would otherwise be discarded. The frame rate can be set at browser
            // creation time via CefBrowserSettings.windowless_frame_rate or changed
            // dynamically using CefBrowserHost::SetWindowlessFrameRate. In cefclient
            // it can be set via the command-line using `--off-screen-frame-rate=XX`.
            // See https://bitbucket.org/chromiumembedded/cef/issues/1368 for details.
            _cefCommandLineArgs->Add("enable-begin-frame-scheduling", "1");
        }

        /// <summary>
        /// Disable Surfaces so internal PDF viewer works for OSR
        /// https://bitbucket.org/chromiumembedded/cef/issues/1689
        /// </summary>
        void EnableInternalPdfViewerOffScreen()
        {
            _cefCommandLineArgs->Add("disable-surfaces", "1");
        }
    };
}
