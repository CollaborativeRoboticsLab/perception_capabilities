#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/runner_base.hpp>
#include <fp_perception_capabilities/TranscribeRunner.hpp>
#include <fp_perception_capabilities/SpeechRunner.hpp>
#include <fp_perception_capabilities/SentimentRunner.hpp>
#include <fp_perception_capabilities/ImageAnalysisRunner.hpp>

// // register runner plugins
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::TranscribeRunner, capabilities2_runner::RunnerBase);
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::SpeechRunner, capabilities2_runner::RunnerBase);
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::SentimentRunner, capabilities2_runner::RunnerBase);
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::ImageAnalysisRunner, capabilities2_runner::RunnerBase);
