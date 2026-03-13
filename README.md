# perception_capabilities

Provides runners for Perception stack.

## Supported runners

| Runner | Description  |
| ---    | ---          |
| Image Analysis runner | provides functionality to analyze images based on a prompt |
| Sentiment runner | Provides sentiment analysis functionality  |
| Speech runner | Provides text to speech functionality  |
| Transcribe runner | Provides speech to text functionality  |

## Examples

Examples depend on [CollaborativeRoboticsLab/capabilities2](https://github.com/CollaborativeRoboticsLab/capabilities2), [CollaborativeRoboticsLab/perception](https://github.com/CollaborativeRoboticsLab/perception) and [CollaborativeRoboticsLab/prompt_tools](https://github.com/CollaborativeRoboticsLab/prompt_tools).

| Example | Description |
| ---     | ---         |
| [Example 1](./docs/example_1.md) | Implements moving the robot to a position and checking the environment via vision and explaining what is there |
| [Example 2](./docs/example_2.md) | Implements moving the robot to a position and checking if there is a person and, if there is asking for the name and speaking it after returning. | 
| [Example 3](./docs/example_3.md) | Implements moving the robot to a position and checking if there is a person and, if there is asking for the name and speaking it after returning. If there is no person, it will move to a different position. | 

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