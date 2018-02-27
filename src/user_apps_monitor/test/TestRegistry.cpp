#ifndef APPIMAGE_DESKTOP_INTEGRATION_TESTREGISTRY_H
#define APPIMAGE_DESKTOP_INTEGRATION_TESTREGISTRY_H

#include <gtest/gtest.h>
#include <QDebug>

#include <Registry.h>

namespace NX_SOFTWARE_CENTER_TESTS {
    class TestRegistry : public testing::Test {
    public:
        TestRegistry() {
            registry.setDataLocations({TEST_DATA_DIR});
            registry.setAppimageLocations({TEST_DATA_DIR"/appimages"});
        }

        Registry registry;
    };

    TEST_F(TestRegistry, getHashFromPath) {
        auto path = "/some/place/appimagekit_e660685f087766d437de39ef24d9d64c-echo.desktop";
        auto result = Registry::getGetHashFromPath(path);

        ASSERT_EQ("e660685f087766d437de39ef24d9d64c", result.toLocal8Bit());
    }

    TEST_F(TestRegistry, findDeployedDesktopFiles) {
        auto entries = registry.getDesktopEntriesPaths();
        QDir dir(TEST_DATA_DIR"/applications");
        for (const QString &entry: dir.entryList({"*.desktop"})) {
            const QString absolutePath = dir.absoluteFilePath(entry);
            ASSERT_TRUE(entries.contains(absolutePath));
        }
    }

    TEST_F(TestRegistry, findDeployedIconsFiles) {
        auto entries = registry.getIconsPaths();
        QDir dir(TEST_DATA_DIR"/icons");
        for (const QString &entry: dir.entryList({"*.png"})) {
            const QString absolutePath = dir.absoluteFilePath(entry);
            ASSERT_TRUE(entries.contains(absolutePath));
        }
    }

    TEST_F(TestRegistry, findDeployedAppimages) {
        auto entries = registry.getAppimagesPaths();

        QDir dir(TEST_DATA_DIR"/appimages");
        auto expected = dir.entryList({"*.AppImage"}, QDir::NoDotAndDotDot | QDir::Files);

        ASSERT_EQ(expected.size(), entries.size());
        for (const QString &entry: expected) {
            const QString absolutePath = dir.absoluteFilePath(entry);
            ASSERT_TRUE(entries.contains(absolutePath));
        }
    }

//    TEST_F(TestRegistry, ) {
//
//    }
}


#endif //APPIMAGE_DESKTOP_INTEGRATION_TESTREGISTRY_H
