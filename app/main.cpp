/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "../src/math/PerformanceTest.hpp"

#include <QApplication>
#include <QPlainTextEdit>
#include <QVulkanInstance>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QPointer>
#include "MainWindow.hpp"

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

//static QPointer<QPlainTextEdit> messageLogWidget;
static QPointer<MainWindow> mainWindow;
static QtMessageHandler oldMessageHandler = nullptr;

static void messageHandler(QtMsgType msgType, const QMessageLogContext &logContext, const QString &text)
{
	if (!mainWindow.isNull()) {
        mainWindow->onLogMessageReceived(text);
	}
    if (oldMessageHandler) {
        oldMessageHandler(msgType, logContext, text);
	}
}

int showQtWindow(int argc, char *argv[]) {
	QApplication app(argc, argv);

	oldMessageHandler = qInstallMessageHandler(messageHandler);
	QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));
	
	mainWindow = new MainWindow();
	mainWindow->onLogMessageReceived(QLatin1String(QLibraryInfo::build()) + QLatin1Char('\n'));

	mainWindow->resize(1024, 768);
	mainWindow->show();
	
	mainWindow->initVulkanWindow();

	int result = app.exec();
	return result;
}

int executePerformanceTest(int argc, char *argv[]) {
	uint nBits = 512;// 2048;
	std::cout << nBits << " random bits: " << ppvr::math::SArbBigInt::randomNumber(nBits,  *ppvr::math::Random::getForLocalThread()).toStringHex() << std::endl << "---" << std::endl;
	ppvr::math::PerformanceTest::modPow();
	
	return 0;
}

int main(int argc, char *argv[]) {
	//int test = 10;
	//while(--test) {
	//	std::cout << test << std::endl;
	//}
	//return 0;
	
	//return executePerformanceTest(argc, argv);
	return showQtWindow(argc, argv);
}
