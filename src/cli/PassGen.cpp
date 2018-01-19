/*
 *  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <stdio.h>

#include "PassGen.h"

#include <QCommandLineParser>
#include <QTextStream>

#include "core/PasswordGenerator.h"

PassGen::PassGen()
{
    this->name = QString("passgen");
    this->description = QObject::tr("Generate a new random password.");
}

PassGen::~PassGen()
{
}

int PassGen::execute(QStringList arguments)
{
    QTextStream inputTextStream(stdin, QIODevice::ReadOnly);
    QTextStream outputTextStream(stdout, QIODevice::WriteOnly);

    QCommandLineParser parser;
    parser.setApplicationDescription(this->description);
    QCommandLineOption lower(QStringList() << "l",
                               QObject::tr("Use lowercase in the generated password."));
    parser.addOption(lower);
    QCommandLineOption upper(QStringList() << "u",
                               QObject::tr("Use uppercase in the generated password."));
    parser.addOption(upper);
    QCommandLineOption numeric(QStringList() << "n",
                               QObject::tr("Use numbers in the generated password."));
    parser.addOption(numeric);
    QCommandLineOption special(QStringList() << "s",
                               QObject::tr("Use special characters in the generated password."));
    parser.addOption(special);
    QCommandLineOption extended(QStringList() << "e",
                               QObject::tr("Use extended ascii in the generated password."));
    parser.addOption(extended);
    parser.addPositionalArgument("length", QObject::tr("Length of the generated password."));
    parser.process(arguments);

    const QStringList args = parser.positionalArguments();
    if (args.size() != 1) {
        outputTextStream << parser.helpText().replace("keepassxc-cli", "keepassxc-cli passgen");
        return EXIT_FAILURE;
    }

    PasswordGenerator passwordGenerator;

    int length = args.at(0).toInt();
    passwordGenerator.setLength(length);

    PasswordGenerator::CharClasses classes = 0x0;

    if (parser.isSet(lower)) {
        classes |= PasswordGenerator::LowerLetters; 
    }
    if (parser.isSet(upper)) {
        classes |= PasswordGenerator::UpperLetters; 
    }
    if (parser.isSet(numeric)) {
        classes |= PasswordGenerator::Numbers; 
    }
    if (parser.isSet(special)) {
        classes |= PasswordGenerator::SpecialCharacters; 
    }
    if (parser.isSet(extended)) {
        classes |= PasswordGenerator::EASCII; 
    }

    if (classes == 0x0) {
        passwordGenerator.setCharClasses(PasswordGenerator::LowerLetters | PasswordGenerator::UpperLetters |
                                         PasswordGenerator::Numbers);
    } else {
        passwordGenerator.setCharClasses(classes);
    }

    if (!passwordGenerator.isValid()) {
        outputTextStream << parser.helpText().replace("keepassxc-cli", "keepassxc-cli passgen");
        return EXIT_FAILURE;
    }

    QString password = passwordGenerator.generatePassword();
    outputTextStream << password << endl;

    return EXIT_SUCCESS;
}