#pragma once
#include <string>
#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/service_runner.hpp>
#include <fp_perception_msgs/srv/perception_sentiment.hpp>

namespace capabilities2_runner
{
/**
 * @brief sentiment runner
 *
 * This class is a wrapper around the capabilities2 service runner and is used to
 * call on the /perception/sentiment_analysis service, providing it as a
 * capability that handles the sentiment analysis of speech data
 */
class SentimentRunner : public ServiceRunner<fp_perception_msgs::srv::PerceptionSentiment>
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
  virtual typename fp_perception_msgs::srv::PerceptionSentiment::Request
  generate_request(capabilities2_events::EventParameters& parameters) override
  {
    fp_perception_msgs::srv::PerceptionSentiment::Request request;

    request.header.frame_id = "";
    request.header.stamp = node_->now();

    request.text = std::any_cast<std::string>(parameters.get_value("text", std::string{}));
    request.use_device_audio = std::any_cast<bool>(parameters.get_value("use_device", false));
    request.audio_request_window = std::any_cast<int>(parameters.get_value("audio_request_window", 0));

    return request;
  }

  /**
   * @brief process the response received from the service server after sending a request
   * 
   * @param response the response received from the service server after sending a request
   */
  virtual void process_response(typename fp_perception_msgs::srv::PerceptionSentiment::Response::SharedPtr response) override
  {
    if (!response)
    {
      RCLCPP_ERROR(node_->get_logger(), "Sentiment response was null");
      return;
    }

    RCLCPP_INFO(node_->get_logger(), "Sentiment label: '%s' (score: %.3f, analyzed_text='%s')", response->label.c_str(),
                response->score, response->analyzed_text.c_str());
  }

  virtual capabilities2_events::EventParameters param_on_success() override
  {
    capabilities2_events::EventParameters params;

    if (!response_)
      return params;

    params.set_value("text", response_->label, capabilities2_events::OptionType::STRING);
    params.set_value("score", response_->score, capabilities2_events::OptionType::DOUBLE);
    params.set_value("analyzed_text", response_->analyzed_text, capabilities2_events::OptionType::STRING);

    return params;
  }
};

}  // namespace capabilities2_runner
