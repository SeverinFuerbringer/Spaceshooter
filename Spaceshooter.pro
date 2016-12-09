TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Engine/Engine.cpp \
    src/Engine/EngineErrorStrings.cpp \
    src/Engine/EngineRandom.cpp \
    src/Engine/GameTime.cpp \
    src/Engine/HUD.cpp \
    src/Engine/MenuButton.cpp \
    src/Engine/MenuElement.cpp \
    src/Engine/MenuWidget.cpp \
    src/Engine/MsgBox.cpp \
    src/Engine/ProgressBar.cpp \
    src/Engine/Scene.cpp \
    src/Engine/Transition.cpp \
    src/Spaceshooter/AnimatedSprite.cpp \
    src/Spaceshooter/Animation.cpp \
    src/Spaceshooter/EnemyShip.cpp \
    src/Spaceshooter/Entity.cpp \
    src/Spaceshooter/Entry.cpp \
    src/Spaceshooter/Fleet.cpp \
    src/Spaceshooter/GameLoop.cpp \
    src/Spaceshooter/Level_000.cpp \
    src/Spaceshooter/MainMenu.cpp \
    src/Spaceshooter/MenuCredits.cpp \
    src/Spaceshooter/MenuOptions.cpp \
    src/Spaceshooter/Projectile.cpp \
    src/Spaceshooter/Ship.cpp \
    src/Spaceshooter/SplashScreen.cpp \
    src/Spaceshooter/Starfield.cpp \
    main.cpp \
    src/Engine/tinyfiledialogs.c

DISTFILES += \
    bin/gfx/fonts/boombox2.ttf \
    bin/gfx/fonts/space_age.ttf \
    bin/audio/Explosion1.wav \
    bin/audio/Explosion2.wav \
    bin/audio/Laser_Shoot.wav \
    bin/audio/Spawn1.wav \
    bin/gfx/Ship2.png \
    bin/gfx/SHIP_a.png \
    bin/gfx/SHIP_F.png \
    bin/gfx/star_1.png \
    bin/gfx/star_3.png \
    Engine/Engine.vcxproj \
    Engine/Engine.vcxproj.filters \
    Spaceshooter/Spaceshooter.rc \
    Spaceshooter/Spaceshooter.vcxproj \
    Spaceshooter/Spaceshooter.vcxproj.filters \
    LICENSE \
    Spaceshooter.sln \
    README.md

HEADERS += \
    Engine/resource.h \
    include/Engine/Engine.h \
    include/Engine/EngineErrorStrings.hpp \
    include/Engine/EngineExport.h \
    include/Engine/EngineMath.hpp \
    include/Engine/EngineRandom.h \
    include/Engine/EngineTypes.hpp \
    include/Engine/GameTime.h \
    include/Engine/HUD.h \
    include/Engine/MenuButton.h \
    include/Engine/MenuElement.h \
    include/Engine/MenuWidget.h \
    include/Engine/MsgBox.h \
    include/Engine/ProgressBar.h \
    include/Engine/Scene.h \
    include/Engine/tinyfiledialogs.h \
    include/Engine/Transition.h \
    include/Spaceshooter/AnimatedSprite.hpp \
    include/Spaceshooter/Animation.hpp \
    include/Spaceshooter/EnemyShip.h \
    include/Spaceshooter/Entity.h \
    include/Spaceshooter/Fleet.h \
    include/Spaceshooter/GameLoop.h \
    include/Spaceshooter/Level_000.h \
    include/Spaceshooter/MainMenu.h \
    include/Spaceshooter/MenuCredits.h \
    include/Spaceshooter/MenuOptions.h \
    include/Spaceshooter/Projectile.h \
    include/Spaceshooter/resource.h \
    include/Spaceshooter/Ship.h \
    include/Spaceshooter/SplashScreen.h \
    include/Spaceshooter/Starfield.h \
    Spaceshooter/resource.h
