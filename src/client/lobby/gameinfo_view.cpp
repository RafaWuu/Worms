//
// Created by xguss on 16/11/23.
//

#include "gameinfo_view.h"

#include <string>

QString GameInfoView::toString(const GameInfo& game) {
    QString id = QString::number(game.id);
    QString scenario = QString::fromStdString(game.name);
    QString players = QString::number(game.players);
    QString max_players = QString::number(game.max_players);
    QString status = QString::fromStdString(std::string(game.status ? "Iniciada" : "Esperando"));

    return QString("ID: %1 - Escenario: %2 - %3/%4 jugadores - Estado: %5")
            .arg(id, scenario, players, max_players, status);
}
