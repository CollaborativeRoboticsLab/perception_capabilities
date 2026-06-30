#pragma once
#include <string>
#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/service_runner.hpp>
#include <perception_msgs/srv/perception_transcribe.hpp>

namespace capabilities2_runner
{
/**
 * @brief transcribe runner
 *
 * This class is a wrapper around the capabilities2 service runner and is used to
 * call on the /perception/transcribe service, providing it as a
 * capability that handles the transcription of perception data
 */
class TranscribeRunner : public ServiceRunner<perception_msgs::srv::PerceptionTranscribe>
{
public:
  TranscribeRunner() : ServiceRunner()
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
    init_service(node, run_config, "/perception/transcription");

    // emit start event
    emit_started(bond_id, "", param_on_started());
  }

protected:
  /**
   * @brief generate a service request from the event parameters provided in the trigger function
   * 
   * @param parameters EventParameters containing parameters for the trigger event
   * @return PerceptionTranscribe::Request the service request to be sent to the service server
   */
  virtual typename perception_msgs::srv::PerceptionTranscribe::Request
  generate_request(capabilities2_events::EventParameters& parameters) override
  {
    perception_msgs::srv::PerceptionTranscribe::Request request;

    request.use_device_audio = std::any_cast<bool>(parameters.get_value("use_device", true));
    request.audio_request_window = std::any_cast<int>(parameters.get_value("audio_request_window", 10));

    if (request.use_device_audio)
    {
      // Use the service request time as the start of the device-audio slice.
      request.audio.header.stamp = node_->now();
      request.audio.header.frame_id = "audio_request_start";
    }

    return request;
  }

  /**
   * @brief process the response received from the service server after sending a request
   * 
   * @param response the response received from the service server after sending a request
   */
  virtual void process_response(typename perception_msgs::srv::PerceptionTranscribe::Response::SharedPtr response) override
  {
    // emit success event with transcribed text as parameter
    if (!response)
    {
      RCLCPP_ERROR(node_->get_logger(), "Transcription response was null");
      return;
    }

    RCLCPP_INFO(node_->get_logger(), "Transcription result: %s", response->transcription.c_str());
  }

  virtual capabilities2_events::EventParameters param_on_success() override
  {
    capabilities2_events::EventParameters params;

    if (!response_)
      return params;

    params.set_value("text", response_->transcription, capabilities2_events::OptionType::STRING);
    params.set_value("success", response_->success, capabilities2_events::OptionType::BOOL);
    
    return params;
  }
};

}  // namespace capabilities2_runner
