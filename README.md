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
| [perception_1.xml](./plans/perception_1.xml) | In this example The LLM would need to generate a plan that moves the robot 1 meter forward, turn left and take a picture. And then try to describe what it sees. |
| [perception_2.xml](./plans/perception_2.xml) | In this example, we define two points as point A and B as world information. The LLM would need to generate a plan or more that moves the robot To the point A and check for a person using vision or audio, then ask for the name. Then it should come back to the origin and repeat the name. | 
| [perception_3.xml](./plans/perception_3.xml) | In this example, we define two points as point A and B as world information. The LLM would need to generate a plan or more that moves the robot To the point A and check for a person using vision or audio, then ask for the name. Then it should come back to the origin and repeat the name. If the person is not there, the robot is supposed to Go to point B instead. | 

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