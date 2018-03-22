//
// Created by alexis on 3/21/18.
//

#ifndef APPPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONFIG_H
#define APPPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONFIG_H


class FirstRunConfig {
public:
    bool isEnabled();

    void enable();

    void disable();

private:
    QString getDesktopFilePath() const;
};


#endif //APPPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONFIG_H
