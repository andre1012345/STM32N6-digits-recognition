 /**
 ******************************************************************************
 * @file    app_config.h
 * @author  GPM Application Team
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef APP_CONFIG
#define APP_CONFIG

#define USE_DCACHE

/*Defines: CMW_MIRRORFLIP_NONE; CMW_MIRRORFLIP_FLIP; CMW_MIRRORFLIP_MIRROR; CMW_MIRRORFLIP_FLIP_MIRROR;*/
#define CAMERA_FLIP CMW_MIRRORFLIP_NONE

#define ASPECT_RATIO_CROP       (1) /* Crop both pipes to nn input aspect ratio; Original aspect ratio kept */
#define ASPECT_RATIO_FIT        (2) /* Resize both pipe to NN input aspect ratio; Original aspect ratio not kept */
#define ASPECT_RATIO_FULLSCREEN (3) /* Resize camera image to NN input size and display a maximized image. See Doc/Build-Options.md#aspect-ratio-mode */
#define ASPECT_RATIO_MODE ASPECT_RATIO_CROP

#define COLOR_BGR (0)
#define COLOR_RGB (1)
#define COLOR_MODE    COLOR_RGB

/* Post-processing type */
#define POSTPROCESS_CLASSIFICATION (0)
#define POSTPROCESS_TYPE POSTPROCESS_CLASSIFICATION

/* Classes */
#define NB_CLASSES   (10)
#define CLASSES_TABLE static const char* classes_table[NB_CLASSES] = {\
    "This number is digit zero",\
    "This number is digit one",\
    "This number is digit two",\
    "This number is digit three",\
    "This number is digit four",\
    "This number is digit five",\
    "This number is digit six",\
    "This number is digit seven",\
    "This number is digit eight",\
    "This number is digit nine"}

/* Display */
#define WELCOME_MSG_1         "mnist_cnn_32x32_int8.onnx"
#define WELCOME_MSG_2         "Model Running on STM32N6570-DK NPU"

#endif
