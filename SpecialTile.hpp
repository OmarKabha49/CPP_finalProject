#include "Tile.hpp"

enum class SpecialType {
    GO,
    JAIL,
    FREE_PARKING,
    GO_TO_JAIL,
    CHANCE,
    COMMUNITY_CHEST,
    INCOME_TAX,
    LUXURY_TAX
};

class SpecialTile : public Tile {
public:
    SpecialTile(const std::string& name, int position, SpecialType type);
    void onLand(Player* player) override;
    SpecialType getType() const { return type; }
private:
    SpecialType type;
};