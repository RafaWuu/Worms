//
// Created by xguss on 16/11/23.
//

#ifndef WORMS_GAMEINFO_VIEW_H
#define WORMS_GAMEINFO_VIEW_H

#include <QString>

#include "gameinfo.h"

class GameInfoView {
public:
    GameInfoView() = default;

    static QString toString(const GameInfo& game);
};
#endif  // WORMS_GAMEINFO_VIEW_H
