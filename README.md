# EcoCircle City Game Design Document

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
    - [Resource Management](#resource-management)
    - [Building Infrastructure](#building-infrastructure)
    - [Circular Economics](#circular-economics)
    - [Environmental Pollution](#environmental-pollution)
    - [Decision Making](#decision-making)
    - [Progression and Goals](#progression-and-goals)
3. [Pollution Circular Economy System](#pollution-circular-economy-system)
    - [Resource System](#resource-system)
    - [Buildings](#buildings)
    - [Mechanics](#mechanics)
4. [Art Style](#art-style)
5. [Sound and Music](#sound-and-music)

---

## Overview

### Concept

A city-building simulation game that emphasizes circular economics and environmental pollution. Players will manage resources, build infrastructures, and make decisions that affect the environment.

### Target Audience

Fans of city-building games and simulation games, particularly those who enjoyed 'Factorio'.

### Platform

PC

### Programming Language

C++

### Libraries

SFML for graphical rendering and input handling

---

## Features

### Resource Management (SFML)

#### Description

Players will manage various types of resources - wood, metal, and energy.

#### Mechanics

Resources will be used to build infrastructures and run the city.

#### SFML

Resource icons and counters will be displayed using SFML's graphical rendering.

### Building Infrastructure (SFML & Custom Code)

#### Description

Players can build different types of buildings like factories, residential areas, and recycling centers.

#### Mechanics

Each building will have its own set of requirements and effects on the environment.

#### SFML

Building icons and placement will be handled through SFML.

#### Custom Code

The logic for building requirements and effects will be custom-coded.

### Circular Economics (Custom Code)

#### Description

Implement a circular economic model where waste materials can be recycled, and the waste materials also affect the strength of enemies.

#### Mechanics

Factories produce waste that can be processed in recycling centers to create new resources.

#### Custom Code

The economic model and recycling algorithms will be custom-coded.

### Environmental Pollution (Custom Code)

#### Description

Pollution will be a key factor affecting the city's health.

#### Mechanics

Factories and waste will increase pollution, while parks and clean energy will reduce it.

#### Custom Code

Pollution algorithms and environmental effects will be custom-coded.

### Decision Making (SFML & Custom Code)

#### Description

Players will make decisions through a UI that affects the city's economy and environment.

#### Mechanics

Decisions could range from policy changes to emergency actions.

#### SFML

Decision UI will be implemented using SFML.

#### Custom Code

The logic for the effects of each decision will be custom-coded.

### Progression and Goals (Custom Code)

#### Description

Players will have specific goals to achieve, like reaching a certain population or reducing pollution.

#### Mechanics

Achieving goals will unlock new buildings and features.

#### Custom Code

Goal tracking and unlocking features will be custom-coded.

---

## Pollution Circular Economy System

### Resource System

#### Types of Resources

1. **Wood**: Used for basic structures and as a fuel source.
2. **Metal**: Used for advanced structures and machinery.
3. **Waste**: Generated by some buildings, contributes to pollution.
4. **Recycled Materials**: Generated by recycling waste, will be used as an index for city's prosperity.
5. **Prosperity**: Used for checking Player's Goal.
6. **Energy**: Required to run most buildings.

### Buildings

#### Waste-Generating Buildings

1. **House**
    - **Description**: Increases Ecnomics
    - **Mechanics**: Consumes Energy, produces prosperity.
    - **Effects**: Increases prosperity.

2. **Factory**
    - **Description**: Produces woods and metal for the city.
    - **Mechanics**: Produces woods, metal, Waste and Energy.
    - **Effects**: Increases pollution levels.
    - **Function**: Essential for economic growth but increases pollution.

3. **Landfill**
    - **Description**: A place to dump waste.
    - **Mechanics**: Stores Waste.
    - **Effects**: Increases pollution over time.
    - **Function**: Provides a way to manage waste but at the cost of increasing pollution.

#### Pollution-Reducing Buildings

1. **Recycling Center**
    - **Description**: Processes waste materials to reduce pollution and create Recycled Materials.
    - **Mechanics**: Consumes waste, produces Recycled Materials.
    - **Effects**: Reduces pollution levels.

2. **Clean Energy Plant**
    - **Description**: Produces energy without adding pollution.
    - **Mechanics**: Consumes recycled material to produce clean energy.
    - **Effects**: Powers the city without increasing pollution.

### Mechanics

#### End Goals for the Player

1. **Sustainable City**: Achieve a city with zero net pollution.
2. **Economic Prosperity**: Reach a certain level of economic output.
3. **Population Milestone**: Grow the city's population to a certain number.
4. **Enemy Defense**: Successfully defend against a set number of enemy waves.

#### Pollution Levels

- **Low Pollution**: Enemies are weak, and the city's health is good.
- **Medium Pollution**: Enemies gain special abilities, and the city's health starts to decline.
- **High Pollution**: Enemies are very strong, and the city's health is poor.

#### Enemy Strength Scaling

- **Low Pollution**: Basic enemies.
- **Medium Pollution**: Enemies with special abilities like shields.
- **High Pollution**: Enemies with advanced abilities like regeneration.

---

## Art Style

- **2D Isometric**: The game will feature a 2D isometric view to give depth to the city-building experience.

## Sound and Music

- **Ambient Sounds**: Background sounds to enhance immersion.
- **Music**: A calming soundtrack that fits the theme of building and managing a city.
