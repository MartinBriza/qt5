/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "ui_tennis.h"

#include <QDialog>

#include <QResizeEvent>
#include <QMoveEvent>
#include <QPropertyAnimation>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothsocket.h>
#include <qbluetoothdevicediscoveryagent.h>

#include "board.h"
#include "controller.h"

#include <QDebug>

QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)

QT_USE_NAMESPACE

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c9");

class TennisServer;
class TennisClient;
//class Handover;

//! [declaration]
class Tennis : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int paddlePos READ paddlePos WRITE setPaddlePos)

public:
    Tennis(QWidget *parent = 0);
    ~Tennis();

    int paddlePos() { return paddle_pos; }
    void setPaddlePos(int p);

signals:
    void moveLeftPaddle(int y);
    void moveRightPaddle(int y);

protected:
    void wheelEvent ( QWheelEvent * event );
    void keyPressEvent ( QKeyEvent * event );
    void resizeEvent(QResizeEvent *);

private slots:
    void serverConnected(const QString &name);
    void serverDisconnected();

    void clientConnected(const QString &name);
    void clientDisconnected();

    void serviceDiscovered(const QBluetoothServiceInfo &serviceInfo);
    void discoveryFinished();

    void startDiscovery();

    void mouseMove(int x, int y);

    void lagReport(int ms);

//    void nearFieldHandover();

    void fps(const QString &f);

private:

    void moveUp(int px = 10);
    void moveDown(int px = 10);

    void move(int px);

    Ui_Tennis *ui;

    Board *board;
    Controller *controller;

    int paddle_pos;
    int endPaddlePos;

    bool isClient;
    bool isConnected;
    bool quickDiscovery;

    QBluetoothSocket *socket;
    TennisServer *server;
    TennisClient *client;

    QPropertyAnimation *paddleAnimation;

    QBluetoothServiceDiscoveryAgent *m_discoveryAgent;
//    Handover *m_handover;
};
//! [declaration]
