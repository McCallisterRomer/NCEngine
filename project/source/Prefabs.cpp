#include "Prefabs.h"
#include "project/components/GamePiece.h"
#include "graphics/materials/Material.h"

using namespace nc;

namespace
{
    bool isInitialized = false;
}

namespace prefab
{
namespace mesh
{
    auto Boar = graphics::Mesh{};
    auto Cattle = graphics::Mesh{};
    auto Coal = graphics::Mesh{};
    auto Disc = graphics::Mesh{};
    auto Dog = graphics::Mesh{};
    auto Donkey = graphics::Mesh{};
    auto Dwarf = graphics::Mesh{};
    auto Grain = graphics::Mesh{};
    auto PlayerBoard = graphics::Mesh{};
    auto Ruby = graphics::Mesh{};
    auto Sheep = graphics::Mesh{};
    auto Stable = graphics::Mesh{};
    auto StartingPlayerPiece = graphics::Mesh{};
    auto Stone = graphics::Mesh{};
    auto Vegetable = graphics::Mesh{};
    auto Wood = graphics::Mesh{};
    auto FurnishingTile = graphics::Mesh{};
}

namespace material
{
    graphics::Material Boar = graphics::Material{};
    graphics::Material Cattle = graphics::Material{};
    graphics::Material Coal = graphics::Material{};
    graphics::Material CoinOne = graphics::Material{};
    graphics::Material CoinTen = graphics::Material{};
    graphics::Material CoinTwo = graphics::Material{};
    graphics::Material Dog = graphics::Material{};
    graphics::Material Donkey = graphics::Material{};
    graphics::Material Dwarf = graphics::Material{};
    graphics::Material Grain = graphics::Material{};
    graphics::Material PlayerBoard = graphics::Material{};
    graphics::Material Ruby = graphics::Material{};
    graphics::Material Sheep = graphics::Material{};
    graphics::Material Stable = graphics::Material{};
    graphics::Material StartingPlayerPiece = graphics::Material{};
    graphics::Material Stone = graphics::Material{};
    graphics::Material Vegetable = graphics::Material{};
    graphics::Material Wood = graphics::Material{};

    graphics::Material FurnishingTileAdditionalDwelling = graphics::Material{};
    graphics::Material FurnishingTileCoupleDwelling = graphics::Material{};
    graphics::Material FurnishingTileDwelling = graphics::Material{};
    graphics::Material FurnishingTileBeerParlor = graphics::Material{};
    graphics::Material FurnishingTileBlacksmithingParlor = graphics::Material{};
    graphics::Material FurnishingTileBlacksmith = graphics::Material{};
    graphics::Material FurnishingTileBreakfastRoom = graphics::Material{};
    graphics::Material FurnishingTileBreedingCave = graphics::Material{};
    graphics::Material FurnishingTileBroomChamber = graphics::Material{};
    graphics::Material FurnishingTileBuilder = graphics::Material{};
    graphics::Material FurnishingTileCarpenter = graphics::Material{};
    graphics::Material FurnishingTileCookingCave = graphics::Material{};
    graphics::Material FurnishingTileCuddleRoom = graphics::Material{};
    graphics::Material FurnishingTileDogSchool = graphics::Material{};
    graphics::Material FurnishingTileFodderChamber = graphics::Material{};
    graphics::Material FurnishingTileFoodChamber = graphics::Material{};
    graphics::Material FurnishingTileGuestRoom = graphics::Material{};
    graphics::Material FurnishingTileHuntingParlor = graphics::Material{};
    graphics::Material FurnishingTileMainStorage = graphics::Material{};
    graphics::Material FurnishingTileMilkingParlor = graphics::Material{};
    graphics::Material FurnishingTileMiner = graphics::Material{};
    graphics::Material FurnishingTileMiningCave = graphics::Material{};
    graphics::Material FurnishingTileMixedDwelling = graphics::Material{};
    graphics::Material FurnishingTileOfficeRoom = graphics::Material{};
    graphics::Material FurnishingTileOreStorage = graphics::Material{};
    graphics::Material FurnishingTilePeacefulCave = graphics::Material{};
    graphics::Material FurnishingTilePrayerChamber = graphics::Material{};
    graphics::Material FurnishingTileQuarry = graphics::Material{};
    graphics::Material FurnishingTileRubySupplier = graphics::Material{};
    graphics::Material FurnishingTileSeam = graphics::Material{};
    graphics::Material FurnishingTileSimpleDwelling = graphics::Material{};
    graphics::Material FurnishingTileSimpleDwelling2 = graphics::Material{};
    graphics::Material FurnishingTileSlaughterCave = graphics::Material{};
    graphics::Material FurnishingTileSparePartStorage = graphics::Material{};
    graphics::Material FurnishingTileStateParlor = graphics::Material{};
    graphics::Material FurnishingTileStoneCarver = graphics::Material{};
    graphics::Material FurnishingTileStoneStorage = graphics::Material{};
    graphics::Material FurnishingTileStoneSupplier = graphics::Material{};
    graphics::Material FurnishingTileStubbleRoom = graphics::Material{};
    graphics::Material FurnishingTileSupplierStorage = graphics::Material{};
    graphics::Material FurnishingTileTrader = graphics::Material{};
    graphics::Material FurnishingTileTreasureChamber = graphics::Material{};
    graphics::Material FurnishingTileWeaponStorage = graphics::Material{};
    graphics::Material FurnishingTileWeavingParlor = graphics::Material{};
    graphics::Material FurnishingTileWoodSupplier = graphics::Material{};
    graphics::Material FurnishingTileWorkingCave = graphics::Material{};
    graphics::Material FurnishingTileWorkRoom = graphics::Material{};
    graphics::Material FurnishingTileWritingChamber = graphics::Material{};
}

void InitializeResources()
{
    if(isInitialized)
    {
        return;
    }
    isInitialized = true;
    
    mesh::Boar = graphics::Mesh{"project//Models//BoarPiece.fbx"};
    mesh::Cattle = graphics::Mesh{"project//Models//CattlePiece.fbx"};
    mesh::Coal = graphics::Mesh{"project//Models//CoalPiece.fbx"};
    mesh::Disc = graphics::Mesh{"project//Models//Disc.fbx"};
    mesh::Dog = graphics::Mesh{"project//Models//DogPiece.fbx"};
    mesh::Donkey = graphics::Mesh{"project//Models//DonkeyPiece.fbx"};
    mesh::Grain = graphics::Mesh{"project//Models//GrainPiece.fbx"};
    mesh::Ruby = graphics::Mesh{"project//Models//RubyPiece.fbx"};
    mesh::Sheep = graphics::Mesh{"project//Models//SheepPiece.fbx"};
    mesh::Stable = graphics::Mesh{"project//Models//StablePiece.fbx"};
    mesh::StartingPlayerPiece = graphics::Mesh{"project//Models//StartingPlayerPiece.fbx"};
    mesh::Stone = graphics::Mesh{"project//Models//StonePiece.fbx"};
    mesh::Vegetable = graphics::Mesh{"project//Models//VegetablePiece.fbx"};
    mesh::Wood = graphics::Mesh{"project//Models//WoodPiece.fbx"};
    mesh::FurnishingTile = graphics::Mesh{"project/Models/FurnishingTile.fbx"};
    mesh::PlayerBoard = graphics::Mesh{"project/Models/PlayerBoard.fbx"};

    material::Boar = graphics::Material{{"project//Textures//BoarPiece_Material_BaseColor.png", "project//Textures//BoarPiece_Material_Normal.png",  "project//Textures//BoarPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Cattle = graphics::Material{{"project//Textures//CattlePiece_Material_BaseColor.png", "project//Textures//CattlePiece_Material_Normal.png",  "project//Textures//CattlePiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Coal = graphics::Material{{"project//Textures//CoalPiece_Material_BaseColor.png", "project//Textures//CoalPiece_Material_Normal.png",  "project//Textures//CoalPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::CoinOne = graphics::Material{{"project//Textures//OneCoinPiece_Material_BaseColor.png", "project//Textures//CoinPiece_Material_Normal.png",  "project//Textures//CoinPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::CoinTwo = graphics::Material{{"project//Textures//TwoCoinPiece_Material_BaseColor.png", "project//Textures//CoinPiece_Material_Normal.png",  "project//Textures//CoinPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::CoinTen = graphics::Material{{"project//Textures//TenCoinPiece_Material_BaseColor.png", "project//Textures//CoinPiece_Material_Normal.png",  "project//Textures//CoinPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Dog = graphics::Material{{"project//Textures//DogPiece_Material_BaseColor.png", "project//Textures//DogPiece_Material_Normal.png",  "project//Textures//DogPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Donkey = graphics::Material{{"project//Textures//DonkeyPiece_Material_BaseColor.png", "project//Textures//DonkeyPiece_Material_Normal.png",  "project//Textures//DonkeyPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Dwarf = graphics::Material{{"nc//source//graphics//DefaultTexture.png", "project//Textures//DwarfDisc_Material_Normal.png",  "project//Textures//DwarfDisc_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Grain = graphics::Material{{"project//Textures//GrainPiece_Material_BaseColor.png", "project//Textures//GrainPiece_Material_Normal.png",  "project//Textures//GrainPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Ruby = graphics::Material{{"project//Textures//RubyPiece_Material_BaseColor.png", "project//Textures//RubyPiece_Material_Normal.png",  "project//Textures//RubyPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Sheep = graphics::Material{{"project//Textures//SheepPiece_Material_BaseColor.png", "project//Textures//SheepPiece_Material_Normal.png",  "project//Textures//SheepPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Stable = graphics::Material{{"nc//source//graphics//DefaultTexture.png", "project//Textures//StablePiece_Material_Normal.png",  "project//Textures//StablePiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::StartingPlayerPiece = graphics::Material{{"project//Textures//StartingPlayerPiece_Material_BaseColor.png", "project//Textures//StartingPlayerPiece_Material_Normal.png",  "project//Textures//StartingPlayerPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Stone = graphics::Material{{"project//Textures//StonePiece_Material_BaseColor.png", "project//Textures//StonePiece_Material_Normal.png",  "project//Textures//StonePiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Vegetable = graphics::Material{{"project//Textures//VegetablePiece_Material_BaseColor.png", "project//Textures//VegetablePiece_Material_Normal.png",  "project//Textures//VegetablePiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::Wood = graphics::Material{{"project//Textures//WoodPiece_Material_BaseColor.png", "project//Textures//WoodPiece_Material_Normal.png",  "project//Textures//WoodPiece_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileAdditionalDwelling = graphics::Material{{"project//Textures//FurnishingTiles//FT_AdditionalDwelling_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileCoupleDwelling = graphics::Material{{"project//Textures//FurnishingTiles//FT_CoupleDwelling_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileDwelling = graphics::Material{{"project//Textures//FurnishingTiles//FT_Dwelling_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBeerParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_BeerParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBlacksmithingParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_BlacksmithingParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBlacksmith = graphics::Material{{"project//Textures//FurnishingTiles//FT_Blacksmith_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBreakfastRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_BreakfastRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBreedingCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_BreedingCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBroomChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_BroomChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileBuilder = graphics::Material{{"project//Textures//FurnishingTiles//FT_Builder_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileCarpenter = graphics::Material{{"project//Textures//FurnishingTiles//FT_Carpenter_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileCookingCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_CookingCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileCuddleRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_CuddleRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileDogSchool = graphics::Material{{"project//Textures//FurnishingTiles//FT_DogSchool_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileFodderChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_FodderChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileFoodChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_FoodChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileGuestRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_GuestRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileHuntingParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_HuntingParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileMainStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_MainStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileMilkingParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_MilkingParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileMiner = graphics::Material{{"project//Textures//FurnishingTiles//FT_Miner_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileMiningCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_MiningCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileMixedDwelling = graphics::Material{{"project//Textures//FurnishingTiles//FT_MixedDwelling_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileOfficeRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_OfficeRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileOreStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_OreStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTilePeacefulCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_PeacefulCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTilePrayerChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_PrayerChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileQuarry = graphics::Material{{"project//Textures//FurnishingTiles//FT_Quarry_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileRubySupplier = graphics::Material{{"project//Textures//FurnishingTiles//FT_RubySupplier_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSeam = graphics::Material{{"project//Textures//FurnishingTiles//FT_Seam_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSimpleDwelling = graphics::Material{{"project//Textures//FurnishingTiles//FT_SimpleDwelling_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSimpleDwelling2 = graphics::Material{{"project//Textures//FurnishingTiles//FT_SimpleDwelling2_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSlaughterCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_SlaughteringCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSparePartStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_SparePartStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileStateParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_StateParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileStoneCarver = graphics::Material{{"project//Textures//FurnishingTiles//FT_StoneCarver_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileStoneStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_StoneStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileStoneSupplier = graphics::Material{{"project//Textures//FurnishingTiles//FT_StoneSupplier_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileStubbleRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_StubbleRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileSupplierStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_SuppliesStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileTrader = graphics::Material{{"project//Textures//FurnishingTiles//FT_Trader_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileTreasureChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_TreasureChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWeaponStorage = graphics::Material{{"project//Textures//FurnishingTiles//FT_WeaponStorage_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWeavingParlor = graphics::Material{{"project//Textures//FurnishingTiles//FT_WeavingParlor_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWoodSupplier = graphics::Material{{"project//Textures//FurnishingTiles//FT_WoodSupplier_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWorkingCave = graphics::Material{{"project//Textures//FurnishingTiles//FT_WorkingCave_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWorkRoom = graphics::Material{{"project//Textures//FurnishingTiles//FT_WorkRoom_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::FurnishingTileWritingChamber = graphics::Material{{"project//Textures//FurnishingTiles//FT_WritingChamber_Material_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
    material::PlayerBoard = graphics::Material{{"project//Textures//PlayerBoard_DefaultMaterial_BaseColor.png", "nc//source//graphics//DefaultTexture_Normal.png", "nc//source//graphics//DefaultTexture.png", "nc//source//graphics//DefaultTexture.png"}};
}

template<> EntityHandle Create<Boar>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Boar, material::Boar);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Cattle>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Cattle, material::Cattle);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Coal>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Coal, material::Coal);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<CoinOne>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Disc, material::CoinOne);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<CoinTwo>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Disc, material::CoinTwo);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<CoinTen>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Disc, material::CoinTen);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Dog>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Dog, material::Dog);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Donkey>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Donkey, material::Donkey);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Dwarf>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Disc, material::Dwarf);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Grain>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Grain, material::Grain);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Ruby>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Ruby, material::Ruby);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Sheep>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Sheep, material::Sheep);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Stable>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Stable, material::Stable);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<StartingPlayerPiece>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::StartingPlayerPiece, material::StartingPlayerPiece);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Stone>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Stone, material::Stone);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Vegetable>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Vegetable, material::Vegetable);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<Wood>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::Wood, material::Wood);
    auto transform = Ecs::GetComponent<Transform>(handle);
    Ecs::AddComponent<project::GamePiece>(handle, transform);
    return handle;
}

template<> EntityHandle Create<PlayerBoard>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::PlayerBoard, material::PlayerBoard);
    return handle;
}

template<> EntityHandle Create<FurnishingTileAdditionalDwelling>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileAdditionalDwelling);
    return handle;
}

template<> EntityHandle Create<FurnishingTileCoupleDwelling>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileCoupleDwelling);
    return handle;
}

template<> EntityHandle Create<FurnishingTileDwelling>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileDwelling);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBeerParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBeerParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBlacksmithingParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBlacksmithingParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBlacksmith>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBlacksmith);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBreakfastRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBreakfastRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBreedingCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBreedingCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBroomChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBroomChamber);
    return handle;
}

template<> EntityHandle Create<FurnishingTileBuilder>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileBuilder);
    return handle;
}

template<> EntityHandle Create<FurnishingTileCarpenter>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileCarpenter);
    return handle;
}

template<> EntityHandle Create<FurnishingTileCookingCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileCookingCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTileCuddleRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileCuddleRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileDogSchool>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileDogSchool);
    return handle;
}

template<> EntityHandle Create<FurnishingTileFodderChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileFodderChamber);
    return handle;
}

template<> EntityHandle Create<FurnishingTileFoodChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileFoodChamber);
    return handle;
}

template<> EntityHandle Create<FurnishingTileGuestRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileGuestRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileHuntingParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileHuntingParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileMainStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileMainStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTileMilkingParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileMilkingParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileMiner>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileMiner);
    return handle;
}

template<> EntityHandle Create<FurnishingTileMiningCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileMiningCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTileMixedDwelling>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileMixedDwelling);
    return handle;
}

template<> EntityHandle Create<FurnishingTileOfficeRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileOfficeRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileOreStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileOreStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTilePeacefulCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTilePeacefulCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTilePrayerChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTilePrayerChamber);
    return handle;
}

template<> EntityHandle Create<FurnishingTileQuarry>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileQuarry);
    return handle;
}

template<> EntityHandle Create<FurnishingTileRubySupplier>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileRubySupplier);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSeam>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSeam);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSimpleDwelling>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSimpleDwelling);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSimpleDwelling2>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSimpleDwelling2);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSlaughterCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSlaughterCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSparePartStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSparePartStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTileStateParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileStateParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileStoneCarver>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileStoneCarver);
    return handle;
}

template<> EntityHandle Create<FurnishingTileStoneStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileStoneStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTileStoneSupplier>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileStoneSupplier);
    return handle;
}

template<> EntityHandle Create<FurnishingTileStubbleRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileStubbleRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileSupplierStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileSupplierStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTileTrader>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileTrader);
    return handle;
}

template<> EntityHandle Create<FurnishingTileTreasureChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileTreasureChamber);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWeaponStorage>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWeaponStorage);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWeavingParlor>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWeavingParlor);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWoodSupplier>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWoodSupplier);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWorkingCave>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWorkingCave);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWorkRoom>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWorkRoom);
    return handle;
}

template<> EntityHandle Create<FurnishingTileWritingChamber>(Vector3 position, Vector3 rotation, Vector3 scale, std::string tag)
{
    auto handle = Ecs::CreateEntity(position, rotation, scale, tag);
    Ecs::AddComponent<Renderer>(handle, mesh::FurnishingTile, material::FurnishingTileWritingChamber);
    return handle;
}
} //end namespace prefab