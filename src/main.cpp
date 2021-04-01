#include <napi.h>

#include <filesystem>

#include <nlohmann/json.hpp>
#include <NifFile.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

Napi::Value Read(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
      return env.Null();
    }

    std::string nif_path_str = info[0].As<Napi::String>();
    nifly::NifFile nif;
    nifly::NiHeader& hdr = nif.GetHeader();

    try {
        fs::path nif_path = fs::path(nif_path_str);
        nif.Load(nif_path);
    }
    catch(const std::exception& e) {
        Napi::Error::New(env, "Couldn't load file " + nif_path_str + ": " + e.what());
        return env.Null();
    }

    json shapes_json = json::array();

    std::vector<nifly::NiShape*> shapes = nif.GetShapes();
    for (std::vector<nifly::NiShape*>::iterator shapes_it = shapes.begin();
        shapes_it != shapes.end();
        ++shapes_it) {
        json shape;
        shape["name"] = (*shapes_it) -> name.get();
        shape["index"] = nif.GetBlockID(*shapes_it);

        nifly::NiShader* shader = nif.GetShader(*shapes_it);
        if (shader) {
            shape["material"] = shader -> name.get();
            shape["wetMaterial"] = shader -> GetWetMaterialName();

            nifly::NiBlockRef<nifly::BSShaderTextureSet>* texture_set_ref = shader -> TextureSetRef();
            if (texture_set_ref) {
                nifly::BSShaderTextureSet* textureSet =
                    hdr.GetBlock<nifly::BSShaderTextureSet>(texture_set_ref);

                int i = 0;
                json textures_json;
                for (std::vector<nifly::NiString>::iterator jt = textureSet -> textures.vec.begin();
                    jt != textureSet -> textures.vec.end();
                    ++jt) {
                        textures_json[std::to_string(i++)] = jt -> get();
                }

                shape["textures"] = textures_json;
                shapes_json.insert(shapes_json.end(), shape);
            }
        }
        
    }

    return Napi::String::New(env, shapes_json.dump());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "read"),
        Napi::Function::New(env, Read, "read")
    );
    return exports;
}

NODE_API_MODULE(index, Init)
