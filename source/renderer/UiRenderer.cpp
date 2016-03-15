#include "UiRenderer.hpp"

#include <cstdio>
#include <vector>
#include <string>

#include <radix/renderer/Renderer.hpp>
#include <radix/model/MeshLoader.hpp>
#include <radix/texture/TextureLoader.hpp>
#include <radix/text/FontLoader.hpp>
#include <radix/shader/ShaderLoader.hpp>
#include <radix/material/MaterialLoader.hpp>
#include <radix/Viewport.hpp>

#include "../Game.hpp"

using namespace radix;

namespace glPortal {

void UiRenderer::render(Renderer &renderer, World &world) {
  glDepthMask(GL_FALSE);
  renderHand(renderer, world);
  int vpWidth, vpHeight;
  renderer.getViewport()->getSize(&vpWidth, &vpHeight);
  Camera camera;
  camera.setOrthographic();
  camera.setBounds(0, vpWidth, 0, vpHeight);
  Matrix4f crosshairMtx;
  crosshairMtx.translate(Vector3f(vpWidth/2, vpHeight/2, -10));
  crosshairMtx.scale(Vector3f(80, 80, 1));
  Matrix4f widget;
  widget.translate(Vector3f(vpWidth/2+12, vpHeight-20, -2));
  widget.scale(Vector3f(380, 80, 1));

  const Mesh &mesh = MeshLoader::getMesh("GUIElement.obj");
  const Material &mat = MaterialLoader::fromTexture("Reticle.png");

  Shader &sh = ShaderLoader::getShader("unshaded.frag");
  renderer.renderMesh(camera, sh, crosshairMtx, mesh, mat);

  // Title
  renderer.setFont("Pacaya", 1.5f);
  renderer.renderText(camera, "GlPortal", Vector3f(25, vpHeight - 75, -20));

  // FPS counter
  renderer.setFont("Pacaya", 0.5f);
  renderer.renderText(camera,
                      std::string("FPS: ") + std::to_string(Game::fps.getFps()),
                      Vector3f(10, vpHeight - 25, -20));
  /*if (renderer.getScene()->screen->enabled){
    renderScreen(renderer);
  }*/
  glDepthMask(GL_TRUE);
}

void UiRenderer::renderScreen(Renderer &renderer, World &world) {
#if 0
  // TODO: restore
  int vpWidth, vpHeight;
  renderer.getViewport()->getSize(&vpWidth, &vpHeight);
  Camera camera;
  camera.setOrthographic();
  camera.setBounds(0, vpWidth, 0, vpHeight);
  Matrix4f widget;
  widget.translate(Vector3f(vpWidth/2, vpHeight/2, -5));
  widget.scale(Vector3f(vpWidth, vpHeight, 1));
  const Mesh &mesh = MeshLoader::getMesh("GUIElement.obj");
  Shader &sh = ShaderLoader::getShader("color.frag");
  Vector4f screenBackgroundColor = renderer.getScene()->screen->backgroundColor;
  glUseProgram(sh.handle);
  glUniform4f(sh.uni("color"),
              screenBackgroundColor.r,
              screenBackgroundColor.g,
              screenBackgroundColor.b,
              screenBackgroundColor.a);
  renderer.renderMesh(camera, sh, widget, mesh, nullptr);
  renderer.setFontColor(renderer.getScene()->screen->textColor);
  renderer.setFontSize(4);
  renderer.renderText(camera, renderer.getScene()->screen->title,
    Vector3f((vpWidth/2)-(renderer.getTextWidth(renderer.getScene()->screen->title)/2),
             vpHeight/2, -1));
  renderer.setFontSize(0.5);
  renderer.renderText(camera, renderer.getScene()->screen->text,
    Vector3f((vpWidth/2)-(renderer.getTextWidth(renderer.getScene()->screen->text)/2),
             (vpHeight/2)-100, -1));
#endif
}

void UiRenderer::renderHand(Renderer &renderer, World &world) {
  int vpWidth, vpHeight;
  renderer.getViewport()->getSize(&vpWidth, &vpHeight);
  Camera camera;
  camera.setOrthographic();
  camera.setBounds(0, vpWidth, 0, vpHeight);
  Matrix4f widget;
  widget.translate(Vector3f(vpWidth-400, 250, -50));
  widget.scale(Vector3f(960, 540, 1));
  const Mesh &mesh = MeshLoader::getMesh("GUIElement.obj");
  const Material &mat = MaterialLoader::fromTexture("hand.png");
  Shader &sh = ShaderLoader::getShader("unshaded.frag");
  //glUniform4f(sh.uni("color"), 0, 0, 0, renderer.getScene()->screen->alpha);
  renderer.renderMesh(camera, sh, widget, mesh, mat);
}

} /* namespace glPortal */
