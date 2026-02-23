#pragma once
#include <string>
#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/service_runner.hpp>
#include <perception_msgs/srv/perception_speech.hpp>

namespace capabilities2_runner
{
/**
 * @brief speech runner
 *
 * This class is a wrapper around the capabilities2 service runner and is used to
 * call on the /perception/speech service, providing it as a
 * capability that handles the transcription of speech data
 */
class SpeechRunner : public ServiceRunner<perception_msgs::srv::PerceptionSpeech>
{
public:
  SpeechRunner() : ServiceRunner()
  {
  }

  /**
   * @brief Starter function for starting the service runner
   *
   * @param node shared pointer to the capabilities node. Allows to use ros node related functionalities
   * @param run_config runner configuration loaded from the yaml file
   */
  virtual void start(rclcpp::Node::SharedPtr node, const runner_opts& run_config, const std::string& bond_id) override
  {
    init_service(node, run_config, "/perception/speech");

    // emit start event
    emit_started(bond_id, "", param_on_started());
  }

protected:
  /**
   * @brief generate a service request from the event parameters provided in the trigger function
   * 
   * @param parameters EventParameters containing parameters for the trigger event
   * @return PerceptionSpeech::Request the service request to be sent to the service server
   */
  virtual typename perception_msgs::srv::PerceptionSpeech::Request
  generate_request(capabilities2_events::EventParameters& parameters) override
  {
    perception_msgs::srv::PerceptionSpeech::Request request;
    
    request.use_device_audio = std::any_cast<bool>(parameters.get_value("use_device_audio", true));
    request.input.text = std::any_cast<std::string>(parameters.get_value("text", std::string{}));

    return request;
  }

  /**
   * @brief process the response received from the service server after sending a request
   * 
   * @param response the response received from the service server after sending a request
   */
  virtual void process_response(typename perception_msgs::srv::PerceptionSpeech::Response::SharedPtr response) override
  {
    // emit success event with transcribed text as parameter
    if (!response)
    {
      RCLCPP_ERROR(node_->get_logger(), "Speech response was null");
      return;
    }

    if (response->success)
    {
      RCLCPP_INFO(node_->get_logger(), "Speech synthesis successful");
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Speech synthesis failed.");
    }
  }
};

}  // namespace capabilities2_runner
