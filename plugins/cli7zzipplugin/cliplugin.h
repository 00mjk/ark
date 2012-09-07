/*
 * ark -- archiver for the KDE project
 *
 * Copyright (C) 2009 Harald Hvaal <haraldhv@stud.ntnu.no>
 * Copyright (C) 2009-2010 Raphael Kubo da Costa <kubito@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */


#ifndef CLIPLUGIN_H
#define CLIPLUGIN_H

#include "kerfuffle/cliinterface.h"

class CliPlugin : public Kerfuffle::CliInterface
{
    Q_OBJECT

public:
    explicit CliPlugin(QObject *parent, const QVariantList & args);
    virtual ~CliPlugin();

    void saveLastLine(const QString & line);
    QString fileExistsName();

protected:
    virtual Kerfuffle::ParameterList parameterList() const;
    virtual bool readListLine(const QString &line);
    virtual void resetReadState();

private:
    enum ArchiveType {
	ArchiveType7z = 0,
	ArchiveTypeBZip2,
	ArchiveTypeGZip,
	ArchiveTypeTar,
	ArchiveTypeZip
    };

    enum ReadState {
	ReadStateHeader = 0,
	ReadStateArchiveInformation,
	ReadStateEntryInformation
    };

    ArchiveType m_archiveType;
    Kerfuffle::ArchiveEntry m_currentArchiveEntry;
    ReadState m_state;
    int m_numberOfVolumes;
    QString m_lastLine;
};

#endif // CLIPLUGIN_H
