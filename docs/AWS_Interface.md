# AWS Interface

The FSY-Eye connects to AWS for two reasons, to upload status messages and images, and to expose an interface from which it can be configured.

Uploaded images are not a stream and sent with a relatively low frequency, with the purpose of long-term storage.

## Configuration commands

The FSU-Eye can process commands that targets it services according to sc_service_list_t, as defined in include/system_controller.h. An action needs to be a command on that service, as defined in relevant service file, and described further down. The FSU-Eye listens for commands on topic 'fsu/eye/<thing-name>/r/command'.

A command message has the following syntax:

```json
{
  "id":<thing_name>,
  "service_id":<service>,
  "command_id":<command>
  [...]
}
```
where the extra option indicates arguments required for the service the message is directed to.

NOTE: As jsmn is used as a JSON parser we do not use nested json messages.

## Services

The defined services can be seen in the below table, together with their relevant service id. These commands are internally used by the application in order to execute services and are not always designed for console use.

Service name | Service ID
------ | ------
WiFi | 1
AWS | 2
Camera | 3
KVS | 4

### WiFi

The Wifi service does not define any commands right now

### AWS

The AWS service defines the following commands

AWS Command | Command ID | Description | Note
------ | ------ | ------ | ------
Connect and Subscribe | 0 | Connects over MQTT, then subscribes to the command topic | N/A over IoT Console
Publish Message | 1 | Sends a provided message on the info topic | N/A over IoT Console
Publish Image | 0 | Sends a provided image on the image topic | N/A over IoT Console

### Camera

The Camera service defines the following commands

Camera Command | Command ID | Description | Note
------ | ------ | ------ | ------
Capute and Send Image | 0 | Request the Camera to capture an image and send it to the image topic |

### KVS

The KVS Command defines the following commands

KVS Command | Command ID | Description | Note
------ | ------ | ------ | ------
Get KVS Key Value | 0 | Request a KVS Value based on a Key | N/A over IoT Console
Set KVS Key Value | 1 | Set a KVS Value for provided Key | Needs additional arguments for command JSON

A list of KVS Entries can be seen here:

Key ID | Description | Note
------ | ------- | ------
WiFi SSID | Name of the WiFi which to conncet to | Need a reset to take effect
WiFi Password | Password of the WiFi which to conncet to | Need a reset to take effect
Image Report Interval | Integer dictating the interval in seconds at which to take and send a picture |
Info Report Interval | Integer dictating the interval in seconds at which to upload diagnostics |

The JSON message when sending a KVS command looks like this
```json
{
  "id":<thing_name>,
  "service_id":"4",
  "command_id":<command>
  "kvs key":<key>
  "kvs value":<value>
}
```

## MQTT Uploads

The FSU-Eye uploads both images and status messages on regular intervals.

### Image

Images are sent periodically, as defined in the main application. For cost-efficiency reasons they are sent to 'basic-ingest', i.e. they can not be subscribed to as ordinary MQTT messages. The basic-ingest topic for images are '$aws/rules/images_to_s3/fsu/eye/<thing-name>/image', where the substring '$aws/rules/image_to_s3' forces the message to a IoT Core rule named 'image_to_s3'. The user needs to define this rule.

### Info

Info messages are sent periodically, as defined in the main application. For cost-efficiency reasons they are sent to 'basic-ingest', i.e. they can not be subscribed to as ordinary MQTT messages. The basic-ingest topic for images are '$aws/rules/info_to_s3/fsu/eye/<thing-name>/info', where the substring '$aws/rules/info_to_s3' forces the message to a IoT Core rule named 'info_to_s3'. The user needs to define this rule.

