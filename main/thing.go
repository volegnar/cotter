components {
  id: "script"
  component: "/main/thing.script"
}
embedded_components {
  id: "sprite"
  type: "sprite"
  data: "default_animation: \"ArrowIcon\"\n"
  "material: \"/builtins/materials/sprite.material\"\n"
  "textures {\n"
  "  sampler: \"texture_sampler\"\n"
  "  texture: \"/resources/ui.atlas\"\n"
  "}\n"
  ""
  scale {
    x: 0.5
    y: 0.5
  }
}
