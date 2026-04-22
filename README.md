# perception_capabilities

Provides runners for Perception stack and example plans shows how these can be used to interpret the surroundings of the robot and use that information for decision making. These runners are used by the LLM to gather information about the surroundings of the robot and to interpret that information.

## Supported runners

| Runner | Description  |
| ---    | ---          |
| Image Analysis runner | provides functionality to analyze images based on a prompt |
| Sentiment runner | Provides sentiment analysis functionality  |
| Speech runner | Provides text to speech functionality  |
| Transcribe runner | Provides speech to text functionality  |

For information about these runners' interfaces, please refer to [Interface Information](./docs/interface.md) section.


## Examples

Examples depend on [CollaborativeRoboticsLab/capabilities2](https://github.com/CollaborativeRoboticsLab/capabilities2), [CollaborativeRoboticsLab/perception](https://github.com/CollaborativeRoboticsLab/perception) and [CollaborativeRoboticsLab/prompt_tools](https://github.com/CollaborativeRoboticsLab/prompt_tools).

| Example | Description |
| ---     | ---         |
| [perception_1.xml](./plans/perception_1.xml) | In this example a photo is captured and analyzed using the LLM. |
| [perception_2.xml](./plans/perception_2.xml) | In this example, a text is played as speech using the Speech runner. |
| [perception_3.xml](./plans/perception_3.xml) | In this example, a text is played first and then a audio clip is captured and transcribed.|
| [perception_4.xml](./plans/perception_4.xml) | In this example, a text is played first and then a audio clip is captured and analyzed for the user's mood |
| [perception_5.xml](./plans/perception_5.xml) | In this example, a LLM is requested to capture an image and explain what it sees. |
| [perception_6.xml](./plans/perception_6.xml) | In this example, a LLM is requested to check how the day is for the user. |
| [perception_7.xml](./plans/perception_7.xml) | In this example, a LLM is requested to check how the day is for the user and provide a summary of their mood. |


To run the examples, first make sure that the robot is running and then on seperate terminals run,

```bash
source install/setup.bash
ros2 launch capabilities2_server capabilities2_server.launch.py
```

```bash
export OPENAI_API_KEY=
source install/setup.bash
ros2 launch perception server.launch.py
```

```bash
export OPENAI_API_KEY=
source install/setup.bash
ros2 launch prompt_bridge prompt_bridge.launch.py
```

```bash
source install/setup.bash
ros2 launch perception_capabilities system.launch.py filename:=perception_1.xml
```