# EmberEngine campaign minimap

This update adds an optional minimap to the campaign Overworld and Underworld atlas. Click the map icon beside the sound control to show or hide it. The minimap starts hidden when the campaign map opens. It shows the party's animated position and outlines the part of the atlas currently visible. The Overworld preview uses the campaign's exploration fog.

## Install into your EmberEngine checkout

With both repositories cloned as sibling folders, run the following in the EmberEngine checkout. Use a clean feature branch so you can review the update alongside any pending work.

```powershell
git switch -c feature/overworld-minimap
git apply --check ../EmberCloud/overworld-minimap.patch
git apply ../EmberCloud/overworld-minimap.patch
Copy-Item ../EmberCloud/apps/sandbox/OverworldMinimap.h apps/sandbox/OverworldMinimap.h
git add apps/sandbox/OverworldStage.h apps/sandbox/OverworldMinimap.h
```

The patch was prepared against EmberEngine main at `29a9cbd93fec52d663cab68354ca488ad8b62684`. If the check reports a conflict after pending changes land, apply the hunks alongside the updated campaign HUD code. The header uses the existing ImGui dependency and needs no CMake edits or additional assets.

Build and launch EmberEngine as usual. In the campaign atlas, check that the icon toggles the overlay, the dot follows the party, and the outline tracks panning and zoom. Check that clicking or scrolling over the minimap leaves the atlas alone and that switching to the Underworld updates the image and position.
