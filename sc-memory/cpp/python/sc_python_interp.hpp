#pragma once

#include "../sc_types.hpp"
#include "../utils/sc_lock.hpp"

#include <string>

namespace py
{

class ScPythonInterpreter
{
public:
  _SC_EXTERN static bool Initialize(std::string const & name);
  _SC_EXTERN static void Shutdown();

  /* This function runs specified script. Path to script should be relative to 
   * python.modules_path config value.
   * This function is a thread safe
   */
  _SC_EXTERN static void RunScript(std::string const & scriptName);

  _SC_EXTERN static void AddModulesPath(std::string const & modulesPath);

protected:
  static void CollectModules(StringVector const & modulePath);
  static void CollectModulesInPath(std::string const & path);

private:
  static bool ms_isInitialized;
  static std::wstring ms_name;
  static utils::ScLock m_lock;

  using ModulesMap = std::unordered_map<std::string, std::string>;
  static ModulesMap ms_foundModules;
  
  using ModulePathSet = std::set<std::string>;
  static ModulePathSet ms_modulePaths;
};

} // py