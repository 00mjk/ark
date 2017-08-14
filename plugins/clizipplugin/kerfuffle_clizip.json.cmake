{
    "KPlugin": {
        "Description": "Legacy support for the zip archive format",
        "Description[ca@valencia]": "Implementació pel format d'arxiu «zip» antic",
        "Description[ca]": "Implementació pel format d'arxiu «zip» antic",
        "Description[cs]": "Historická podpora archivačního formátu zip",
        "Description[de]": "Unterstützung für veraltete Zip-Archivformate",
        "Description[el]": "Κληροδοτούμενη υποστήριξη για την αρχειοθήκη μορφής zip",
        "Description[es]": "Uso heredado para el formato de archivo comprimido zip",
        "Description[eu]": "zip artxibo formatuarentzako heredatutako euskarria",
        "Description[fr]": "Prise en charge traditionnelle du format d'archive zip",
        "Description[it]": "Supporto originale per il formato di archivi ZIP",
        "Description[nl]": "Verouderde ondersteuning voor het zip-archiefformaat",
        "Description[nn]": "Støtte for for det eldre arkivformatet ZIP",
        "Description[pl]": "Obsługa przestarzałego formatu archiwów zip",
        "Description[pt]": "Suporte antigo para o formato de pacotes ZIP",
        "Description[sk]": "Spätná podpora pre archívny formát zip",
        "Description[sl]": "Opuščena podpora za arhive vrste zip",
        "Description[sr@ijekavian]": "Подршка за застареле архиве формата ЗИП",
        "Description[sr@ijekavianlatin]": "Podrška za zastarele arhive formata ZIP",
        "Description[sr@latin]": "Podrška za zastarele arhive formata ZIP",
        "Description[sr]": "Подршка за застареле архиве формата ЗИП",
        "Description[sv]": "Stöd för föråldrat zip-arkivformat",
        "Description[tr]": "Zip arşivi biçimi için eski desteği",
        "Description[uk]": "Підтримка архівів у застарілій версії формату zip",
        "Description[x-test]": "xxLegacy support for the zip archive formatxx",
        "Description[zh_CN]": "zip 归档格式的老旧支持",
        "Description[zh_TW]": "對 zip 壓縮格式的舊版支援",
        "Id": "kerfuffle_clizip",
        "MimeTypes": [
            "@SUPPORTED_MIMETYPES@"
        ],
        "Name": "Info-zip plugin",
        "Name[ca@valencia]": "Connector de l'Info-zip",
        "Name[ca]": "Connector de l'Info-zip",
        "Name[cs]": "Modul info-zip",
        "Name[de]": "Info-zip-Modul",
        "Name[el]": "Πρόσθετο Info-zip",
        "Name[es]": "Complemento Info-zip",
        "Name[eu]": "Info-zip plugina",
        "Name[fr]": "Module externe info-zip",
        "Name[it]": "Estensione Info-zip",
        "Name[nl]": "Info-zip-plug-in",
        "Name[nn]": "Info-ZIP-tillegg",
        "Name[pl]": "Wtyczka info-zip",
        "Name[pt]": "'Plugin' do Info-zip",
        "Name[sk]": "Plugin Info-zip",
        "Name[sl]": "Vstavek Info-zip",
        "Name[sr@ijekavian]": "Прикључак за Инфозип",
        "Name[sr@ijekavianlatin]": "Priključak za Info‑ZIP",
        "Name[sr@latin]": "Priključak za Info‑ZIP",
        "Name[sr]": "Прикључак за Инфозип",
        "Name[sv]": "Info-zip-insticksprogram",
        "Name[tr]": "Info-zip eklentisi",
        "Name[uk]": "Додаток info-zip",
        "Name[x-test]": "xxInfo-zip pluginxx",
        "Name[zh_CN]": "Info-zip 插件",
        "Name[zh_TW]": "Info-zip 外掛程式",
        "ServiceTypes": [
            "Kerfuffle/Plugin"
        ],
        "Version": "@KDE_APPLICATIONS_VERSION@"
    },
    "X-KDE-Kerfuffle-ReadOnlyExecutables": [
        "zipinfo",
        "unzip"
    ],
    "X-KDE-Kerfuffle-ReadWrite": true,
    "X-KDE-Kerfuffle-ReadWriteExecutables": [
        "zip"
    ],
    "X-KDE-Priority": 160,
    "application/x-java-archive": {
        "CompressionLevelDefault": 6,
        "CompressionLevelMax": 9,
        "CompressionLevelMin": 0,
        "Encryption": true,
        "SupportsTesting": true
    },
    "application/zip": {
        "CompressionLevelDefault": 6,
        "CompressionLevelMax": 9,
        "CompressionLevelMin": 0,
        "CompressionMethodDefault": "Deflate",
        "CompressionMethods": {
            "BZip2": "bzip2",
            "Deflate": "deflate",
            "Store": "store"
        },
        "Encryption": true,
        "EncryptionMethodDefault": "ZipCrypto",
        "EncryptionMethods": [
            "ZipCrypto"
        ],
        "SupportsTesting": true
    }
}
