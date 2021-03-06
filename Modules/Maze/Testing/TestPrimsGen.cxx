/*===========================================================================================================
 *
 * HUC - Hurna Core
 *
 * Copyright (c) Michael Jeulin-Lagarrigue
 *
 *  Licensed under the MIT License, you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://github.com/Hurna/Hurna-Core/blob/master/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 *=========================================================================================================*/
#include <gtest/gtest.h>
#include <prims_generator.hxx>

using namespace huc;
using namespace maze;

#ifndef DOXYGEN_SKIP
namespace {

}
#endif /* DOXYGEN_SKIP */

// Test Binary Tree Generator
TEST(TestPrimsGen, build)
{
  // 0 x 0 - No Maze
  {
    auto maze = PrimsGenerator()(0, 0);
    EXPECT_EQ(maze, nullptr);
  }

  // 5 x 0 - No Maze
  {
    auto maze = PrimsGenerator()(5, 0);
    EXPECT_EQ(maze, nullptr);
  }

  // 5 x 10 Maze
  {
    auto maze = PrimsGenerator()(5, 10);
    EXPECT_EQ(maze->Width(), 5);
    EXPECT_EQ(maze->Height(), 10);
  }

  // 10 x 10 Maze
  {
    auto maze = PrimsGenerator()(10, 10);
    EXPECT_EQ(maze->Width(), 10);
    EXPECT_EQ(maze->Height(), 10);
  }

  // 10 x 10 Maze - Start from the middle
  {
    auto maze = PrimsGenerator()(10, 10, PrimsGenerator::Point(4, 4));
    EXPECT_EQ(maze->Width(), 10);
    EXPECT_EQ(maze->Height(), 10);
  }

  // 10 x 10 No Maze - StartPoint out of the box
  {
    auto maze = PrimsGenerator()(10, 10, PrimsGenerator::Point(15, 0));
    EXPECT_EQ(maze, nullptr);
  }

  // 10 x 10 No Maze - StartPoint out of the box
  {
    auto maze = PrimsGenerator()(10, 10, PrimsGenerator::Point(10, 10));
    EXPECT_EQ(maze, nullptr);
  }
}
