/*

 ark -- archiver for the KDE project

 Copyright (C)

 1997-1999: Rob Palmbos palm9744@kettering.edu
 1999: Francois-Xavier Duranceau duranceau@kde.org
 1999-2000: Emily Ezust  emilye@corel.com

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <dcopclient.h>
#include <kdebug.h>
#include <kcmdlineargs.h>

#include <qfile.h>

#include "arkapp.h"
#include "arkwidget.h"

ArkApplication *ArkApplication::mInstance = NULL;

ArkApplication * ArkApplication::getInstance()
{
  if (mInstance == NULL)
    mInstance = new ArkApplication();
  return mInstance;
}

ArkApplication::ArkApplication()
  : KUniqueApplication()
{
  kdebug(0, 1601, "+ArkApplication::ArkApplication");
  windowList = new QList<ArkWidget>();
  windowList->setAutoDelete( FALSE );
  kdebug(0, 1601, "-ArkApplication::ArkApplication");
}

int ArkApplication::newInstance()
{
  kdebug(0, 1601, "+ArkApplication::newInstance");

  QString Zip;
  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

  if (args->count() > 0) 
  {
     const char *arg = args->arg(0);
     if (arg[0] == '/')
     {
        Zip = QFile::decodeName(arg);
     }
     else
     {
        Zip = KCmdLineArgs::cwd() + "/" + QFile::decodeName(arg);
     }
  }
  args->clear();

  ArkWidget *arkWin = new ArkWidget();
  arkWin->show();
  arkWin->resize(640, 300);

  if (!Zip.isEmpty())
  {
    arkWin->file_open(Zip);
  }
  kdebug(0, 1601, "-ArkApplication::newInstance");
  return 0;
}

#include "arkapp.moc"
