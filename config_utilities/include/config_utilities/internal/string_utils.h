#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "config_utilities/internal/meta_data.h"

// clang-format off
#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#endif
// clang-format on

namespace config::internal {

inline static const std::string kInvalidField = "<Invalid Field>";

/**
 * @brief Print a string centered in a line.
 * @param text The text to be centered.
 * @param width The width of the line.
 * @param symbol The symbol to fill the line with.
 * @returns The centered string.
 */
std::string printCenter(const std::string& text, int width, char symbol);

/**
 * @brief Split a namespace string into a vector of all non-empty strings separated by a delimiter.
 * @param text The text to be splitNamespace.
 * @param delimiter The delimiter to split the text by.
 * @returns A vector of all single valid namespaces.
 */
std::vector<std::string> splitNamespace(const std::string& text, const std::string& delimiter = "/");

/**
 * @brief Join a vector of strings into a single string separated by a delimiter.
 * @param namespaces Namespaces to be joined. Each element is expected to be a single valid namespace.
 * @param delimiter The delimiter to join the namespaces with.
 * @returns The joined namespace.
 */
std::string joinNamespace(const std::vector<std::string>& namespaces, const std::string& delimiter = "/");

/**
 * @brief Join two arbitrary namespace strings into a single namespace string separated by a delimiter.
 * @param namespace_1 The first namespace.
 * @param namespace_2 The second namespace.
 * @param delimiter The delimiter to split and join the namespaces with.
 * @returns The joined namespace.
 */
std::string joinNamespace(const std::string& namespace_1,
                          const std::string& namespace_2,
                          const std::string& delimiter = "/");

/**
 * @brief Formatting of YAML nodes to strings. Most config types can be neatly represented as low-depth yaml nodes, or
 * should otherwise probably be wrapped in a separate confi struct.
 * @param data The data to be formatted.
 * @returns The formatted string.
 */
std::string dataToString(const YAML::Node& data);

/**
 * @brief Find all occurences of a substring in a string.
 * @param text The text to be searched.
 * @param substring The substring to be searched for.
 * @returns The vector of positions of the substring in the string.
 */
std::vector<size_t> findAllSubstrings(const std::string& text, const std::string& substring);

/**
 * @brief Get a human readable type name of a type if cmopiled with GCC, otherwise default to the mangled typename.
 * @tparam T The type to get the name of.
 */
template <typename T>
inline std::string typeName() {
  // See https://en.cppreference.com/w/cpp/types/type_info/name for more details.
  const char* name = typeid(T).name();
#ifdef __GNUG__
  int status = -4;
  std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, NULL, NULL, &status), std::free};
  return (status == 0) ? res.get() : name;
#else
  return name;
#endif
}

/**
 * @brief Trim any trailing spaces at the end of a string.
 * @param text The line to be trimmed.
 * @returns A version of the string with all trailing whitespace stripped.
 */
std::string pruneTrailingWhitespace(const std::string& text);

/**
 * @brief Trim any leading spaces at the beginning of a string.
 * @param text The line to be trimmed.
 * @returns A version of the string with all leading whitespace stripped.
 */
std::string pruneLeadingWhitespace(const std::string& text);

/**
 * @brief Trim any leading and trailing spaces of a string.
 * @param text The line to be trimmed.
 * @returns A version of the string with all leading and trailing whitespace stripped.
 */
std::string pruneWhitespace(const std::string& text);

/**
 * @brief Wrap a string to a given width, indenting all lines (optionally including the first line) by a given amount.
 * Does not trim leading whitespace on the first line, but leading and trailing whitespace on all other lines.
 * @param str The string to be wrapped.
 * @param width The width to wrap the string to.
 * @param indent The amount of spaces to indent each line by.
 * @param indent_first_line Whether to indent the first line.
 * @returns The wrapped string.
 */
std::string wrapString(const std::string& str, size_t width, size_t indent = 0, bool indent_first_line = true);

}  // namespace config::internal
