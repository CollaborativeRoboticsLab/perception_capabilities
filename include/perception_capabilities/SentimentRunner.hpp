#pragma once
#include <string>
#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/service_runner.hpp>
#include <perception_msgs/srv/perception_sentiment.hpp>

namespace capabilities2_runner
{
/**
 * @brief sentiment runner
 *
 * This class is a wrapper around the capabilities2 service runner and is used to
 * call on the /perception/sentiment_analysis service, providing it as a
 * capability that handles the sentiment analysis of speech data
 */
class SentimentRunner : public ServiceRunner<perception_msgs::srv::PerceptionSentiment>
{
public:
  SentimentRunner() : ServiceRunner()
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
    init_service(node, run_config, "/perception/sentiment_analysis");

    // emit start event
    emit_started(bond_id, "", param_on_started());
  }

protected:
  /**
   * @brief generate a service request from the event parameters provided in the trigger function
   * 
   * @param parameters EventParameters containing parameters for the trigger event
   * @return PerceptionSentiment::Request the service request to be sent to the service server
   */
  virtual typename perception_msgs::srv::PerceptionSentiment::Request
  generate_request(capabilities2_events::EventParameters& parameters) override
  {
    perception_msgs::srv::PerceptionSentiment::Request request;

    request.use_device_audio = std::any_cast<bool>(parameters.get_value("use_device_audio", true));
    request.device_buffer_time = std::any_cast<int>(parameters.get_value("device_buffer_time", 15));

    return request;
  }

  /**
   * @brief process the response received from the service server after sending a request
   * 
   * @param response the response received from the service server after sending a request
   */
  virtual void process_response(typename perception_msgs::srv::PerceptionSentiment::Response::SharedPtr response) override
  {
    if (!response)
    {
      RCLCPP_ERROR(node_->get_logger(), "Sentiment response was null");
      return;
    }

    RCLCPP_INFO(node_->get_logger(), "Sentiment label: '%s' (score: %.3f)", response->label.c_str(), response->score);
  }

  virtual capabilities2_events::EventParameters param_on_success() override
  {
    capabilities2_events::EventParameters params;

    if (!response_)
      return params;

    std::string sentiment_result = "Sentiment analysis result: " + response_->label + " (score: " + std::to_string(response_->score) + ")";
    
    params.set_value("text", sentiment_result, capabilities2_events::OptionType::STRING);

    return params;
  }
};

}  // namespace capabilities2_runner
