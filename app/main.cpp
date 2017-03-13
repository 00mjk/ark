/*
 * ark -- archiver for the KDE project
 *
 * Copyright (C) 2007 Henrique Pinto <henrique.pinto@kdemail.net>
 * Copyright (C) 2008-2009 Harald Hvaal <haraldhv@stud.ntnu.no>
 * Copyright (C) 2015-2016 Ragnar Thomsen <rthomsen6@gmail.com>
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

#include "ark_version.h"
#include "ark_debug.h"
#include "mainwindow.h"
#include "batchextract.h"
#include "addtoarchive.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QByteArray>
#include <QFileInfo>

#include <KAboutData>
#include <KCrash>
#include <KDBusService>
#include <Kdelibs4ConfigMigrator>
#include <KLocalizedString>

using Kerfuffle::AddToArchive;

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts); // Required for the webengine part.
    QApplication application(argc, argv);

    /**
     * enable high dpi support
     */
    application.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    KCrash::initialize();

    // Debug output can be turned on here:
    //QLoggingCategory::setFilterRules(QStringLiteral("ark.debug = true"));

    Kdelibs4ConfigMigrator migrate(QStringLiteral("ark"));
    migrate.setConfigFiles(QStringList() << QStringLiteral("arkrc"));
    migrate.setUiFiles(QStringList() << QStringLiteral("arkuirc"));
    migrate.migrate();

    KLocalizedString::setApplicationDomain("ark");

    KAboutData aboutData(QStringLiteral("ark"),
                         i18n("Ark"),
                         QStringLiteral(ARK_VERSION_STRING),
                         i18n("KDE Archiving tool"),
                         KAboutLicense::GPL,
                         i18n("(c) 1997-2016, The Ark Developers"),
                         QString(),
                         QStringLiteral("http://utils.kde.org/projects/ark")
    );

    aboutData.setOrganizationDomain("kde.org");

    aboutData.addAuthor(i18n("Elvis Angelaccio"),
                        i18n("Maintainer"),
                        QStringLiteral("elvis.angelaccio@kde.org"));
    aboutData.addAuthor(i18n("Ragnar Thomsen"),
                        i18n("Maintainer, KF5 port"),
                        QStringLiteral("rthomsen6@gmail.com"));
    aboutData.addAuthor(i18n("Raphael Kubo da Costa"),
                        i18n("Former Maintainer"),
                        QStringLiteral("rakuco@FreeBSD.org"));
    aboutData.addAuthor(i18n("Harald Hvaal"),
                        i18n("Former Maintainer"),
                        QStringLiteral("haraldhv@stud.ntnu.no"));
    aboutData.addAuthor(i18n("Henrique Pinto"),
                        i18n("Former Maintainer"),
                        QStringLiteral("henrique.pinto@kdemail.net"));
    aboutData.addAuthor(i18n("Helio Chissini de Castro"),
                        i18n("Former maintainer"),
                        QStringLiteral("helio@kde.org"));
    aboutData.addAuthor(i18n("Georg Robbers"),
                        QString(),
                        QStringLiteral("Georg.Robbers@urz.uni-hd.de"));
    aboutData.addAuthor(i18n("Roberto Selbach Teixeira"),
                        QString(),
                        QStringLiteral("maragato@kde.org"));
    aboutData.addAuthor(i18n("Francois-Xavier Duranceau"),
                        QString(),
                        QStringLiteral("duranceau@kde.org"));
    aboutData.addAuthor(i18n("Emily Ezust (Corel Corporation)"),
                        QString(),
                        QStringLiteral("emilye@corel.com"));
    aboutData.addAuthor(i18n("Michael Jarrett (Corel Corporation)"),
                        QString(),
                        QStringLiteral("michaelj@corel.com"));
    aboutData.addAuthor(i18n("Robert Palmbos"),
                        QString(),
                        QStringLiteral("palm9744@kettering.edu"));

    aboutData.addCredit(i18n("Bryce Corkins"),
                        i18n("Icons"),
                        QStringLiteral("dbryce@attglobal.net"));
    aboutData.addCredit(i18n("Liam Smit"),
                        i18n("Ideas, help with the icons"),
                        QStringLiteral("smitty@absamail.co.za"));
    aboutData.addCredit(i18n("Andrew Smith"),
                        i18n("bkisofs code"),
                        QString(),
                        QStringLiteral("http://littlesvr.ca/misc/contactandrew.php"));
    aboutData.addCredit(i18n("Vladyslav Batyrenko"),
                        i18n("Advanced editing functionalities"),
                        QString(),
                        QStringLiteral("http://mvlabat.github.io/ark-gsoc-2016/"));

    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("ark")));

    QCommandLineParser parser;
    parser.setApplicationDescription(aboutData.shortDescription());
    parser.addHelpOption();
    parser.addVersionOption();

    // Url to open.
    parser.addPositionalArgument(QStringLiteral("[urls]"), i18n("URLs to open."));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("d") << QStringLiteral("dialog"),
                                        i18n("Show a dialog for specifying the options for the operation (extract/add)")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("o") << QStringLiteral("destination"),
                                        i18n("Destination folder to extract to. Defaults to current path if not specified."),
                                        QStringLiteral("directory")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("O") << QStringLiteral("opendestination"),
                                        i18n("Open destination folder after extraction.")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("c") << QStringLiteral("add"),
                                        i18n("Query the user for an archive filename and add specified files to it. Quit when finished.")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("t") << QStringLiteral("add-to"),
                                        i18n("Add the specified files to 'filename'. Create archive if it does not exist. Quit when finished."),
                                        QStringLiteral("filename")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("p") << QStringLiteral("changetofirstpath"),
                                        i18n("Change the current dir to the first entry and add all other entries relative to this one.")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("f") << QStringLiteral("autofilename"),
                                        i18n("Automatically choose a filename, with the selected suffix (for example rar, tar.gz, zip or any other supported types)"),
                                        QStringLiteral("suffix")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("b") << QStringLiteral("batch"),
                                        i18n("Use the batch interface instead of the usual dialog. This option is implied if more than one url is specified.")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("e") << QStringLiteral("autodestination"),
                                        i18n("The destination argument will be set to the path of the first file supplied.")));

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("a") << QStringLiteral("autosubfolder"),
                                        i18n("Archive contents will be read, and if detected to not be a single folder archive, a subfolder with the name of the archive will be created.")));

    aboutData.setupCommandLine(&parser);

    KAboutData::setApplicationData(aboutData);

    // Do the command line parsing.
    parser.process(application);

    // Handle standard options.
    aboutData.processCommandLine(&parser);

    // This is needed to prevent Dolphin from freezing when opening an archive.
    KDBusService dbusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    // Session restoring.
    if (application.isSessionRestored()) {
        if (!KMainWindow::canBeRestored(1)) {
            return -1;
        }

        MainWindow* window = new MainWindow;
        window->restore(1);
        if (!window->loadPart()) {
            delete window;
            return -1;
        }
    } else { // New ark window (no restored session).

        // Open any given URLs.
        const QStringList urls = parser.positionalArguments();

        if (parser.isSet(QStringLiteral("add")) ||
            parser.isSet(QStringLiteral("add-to"))) {

            AddToArchive *addToArchiveJob = new AddToArchive(&application);
            application.setQuitOnLastWindowClosed(false);
            QObject::connect(addToArchiveJob, &KJob::result, &application, &QCoreApplication::quit, Qt::QueuedConnection);

            if (parser.isSet(QStringLiteral("changetofirstpath"))) {
                qCDebug(ARK) << "Setting changetofirstpath";
                addToArchiveJob->setChangeToFirstPath(true);
            }

            if (parser.isSet(QStringLiteral("add-to"))) {
                qCDebug(ARK) << "Setting filename to" << parser.value(QStringLiteral("add-to"));
                addToArchiveJob->setFilename(QUrl::fromUserInput(parser.value(QStringLiteral("add-to")),
                                                                 QString(),
                                                                 QUrl::AssumeLocalFile));
            }

            if (parser.isSet(QStringLiteral("autofilename"))) {
                qCDebug(ARK) << "Setting autofilename to" << parser.value(QStringLiteral("autofilename"));
                addToArchiveJob->setAutoFilenameSuffix(parser.value(QStringLiteral("autofilename")));
            }

            for (int i = 0; i < urls.count(); ++i) {
                //TODO: use the returned value here?
                qCDebug(ARK) << "Adding url" << QUrl::fromUserInput(urls.at(i), QString(), QUrl::AssumeLocalFile);
                addToArchiveJob->addInput(QUrl::fromUserInput(urls.at(i), QString(), QUrl::AssumeLocalFile));
            }

            if (parser.isSet(QStringLiteral("dialog"))) {
                qCDebug(ARK) << "Using kerfuffle to open add dialog";
                if (!addToArchiveJob->showAddDialog()) {
                    return 0;
                }
            }

            addToArchiveJob->start();

        } else if (parser.isSet(QStringLiteral("batch"))) {

            BatchExtract *batchJob = new BatchExtract(&application);
            application.setQuitOnLastWindowClosed(false);
            QObject::connect(batchJob, &KJob::result, &application, &QCoreApplication::quit, Qt::QueuedConnection);

            for (int i = 0; i < urls.count(); ++i) {
                qCDebug(ARK) << "Adding url" << QUrl::fromUserInput(urls.at(i), QString(), QUrl::AssumeLocalFile);
                batchJob->addInput(QUrl::fromUserInput(urls.at(i), QString(), QUrl::AssumeLocalFile));
            }

            if (parser.isSet(QStringLiteral("autosubfolder"))) {
                qCDebug(ARK) << "Setting autosubfolder";
                batchJob->setAutoSubfolder(true);
            }

            if (parser.isSet(QStringLiteral("autodestination"))) {
                QString autopath = QFileInfo(QUrl::fromUserInput(urls.at(0), QString(), QUrl::AssumeLocalFile).path()).path();
                qCDebug(ARK) << "By autodestination, setting path to " << autopath;
                batchJob->setDestinationFolder(autopath);
            }

            if (parser.isSet(QStringLiteral("destination"))) {
                qCDebug(ARK) << "Setting destination to " << parser.value(QStringLiteral("destination"));
                batchJob->setDestinationFolder(parser.value(QStringLiteral("destination")));
            }

            if (parser.isSet(QStringLiteral("opendestination"))) {
                qCDebug(ARK) << "Setting opendestination";
                batchJob->setOpenDestinationAfterExtraction(true);
            }

            if (parser.isSet(QStringLiteral("dialog"))) {
                qCDebug(ARK) << "Opening extraction dialog";
                if (!batchJob->showExtractDialog()) {
                    return 0;
                }
            }

            batchJob->start();

        } else {

            MainWindow *window = new MainWindow;
            if (!window->loadPart()) { // if loading the part fails
                delete window;
                return -1;
            }

            if (!urls.isEmpty()) {
                qCDebug(ARK) << "Trying to open" << QUrl::fromUserInput(urls.at(0), QString(), QUrl::AssumeLocalFile);

                if (parser.isSet(QStringLiteral("dialog"))) {
                    window->setShowExtractDialog(true);
                }
                window->openUrl(QUrl::fromUserInput(urls.at(0), QString(), QUrl::AssumeLocalFile));
            }
            window->show();
        }
    }

    qCDebug(ARK) << "Entering application loop";
    return application.exec();
}
